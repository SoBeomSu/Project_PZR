// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/LaserRoom/LaserMirror.h"
#include "KJW/KHelper.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "MotionControllerComponent.h"


#include "NiagaraComponent.h"
#include "NiagaraSystem.h"


#include "KJW/LaserRoom/EndLaserPoint.h"
// Sets default values
ALaserMirror::ALaserMirror()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MirrorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MirrorMeshComp");
	SetRootComponent(MirrorMeshComp);
	
	MirroBoxComp = CreateDefaultSubobject<UBoxComponent>("MirroBoxComp");
	MirroBoxComp->SetupAttachment(MirrorMeshComp);

	TempMirrorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("TempMirrorMeshComp");
	TempMirroBoxComp = CreateDefaultSubobject<UBoxComponent>("TempMirroBoxComp");
	TempMirroBoxComp->SetupAttachment(TempMirrorMeshComp);
	
	MirrorMeshComp->SetCollisionProfileName(TEXT("GrapObject"));
	MirroBoxComp->SetCollisionProfileName(TEXT("Mirror"));
	TempMirroBoxComp->SetCollisionProfileName(TEXT("Mirror"));


	MirrorMeshComp-> SetSimulatePhysics(true);
	TempMirrorMeshComp->SetSimulatePhysics(false);
	TempMirrorMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

// Called when the game starts or when spawned
void ALaserMirror::BeginPlay()
{
	Super::BeginPlay();
	OrginScale = GetActorScale3D().X;
	TempMirrorMeshComp->SetRelativeScale3D(FVector(OrginScale));
	TempMirrorMeshComp->SetVisibility(false);

	TempMirroBoxComp->SetRelativeLocation(MirroBoxComp->GetRelativeLocation());
	TempMirroBoxComp->SetRelativeRotation(MirroBoxComp->GetRelativeRotation());
	TempMirroBoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TempMirroBoxComp->SetBoxExtent(MirroBoxComp->GetUnscaledBoxExtent());

}

// Called every frame
void ALaserMirror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawTempMirror();
}



void ALaserMirror::NextLaserStart(const FHitResult& HitInfo, const FVector& InDir, const float& LaserLength, TArray<FVector>& Lines, bool& IsGoal, bool& IsReal)
{
	//가짜 빛인지 체크하기
	if (IsReal && HitInfo.GetComponent() == TempMirroBoxComp)
	{
		IsReal = false;
	}


	//1. 들어온 레이저의 반사 방향 구하기
	FVector SurfaceNormal = HitInfo.ImpactNormal;
	FVector StartPoint = HitInfo.Location;
	FVector ReflectionVector = KHelper::GetReflectionVector(InDir, SurfaceNormal);

	//2. 최종 다음 레이저 위치 구하기
	//FVector ReflectionVector = InDir.MirrorByVector(SurfaceNormal);
	FVector EndPoint = StartPoint + (ReflectionVector * LaserLength);

	//3.라인 트레이스로 다음 충돌체 확인
	FHitResult MirrorHitInfo;
	ALaserMirror* NextMirror = nullptr;
	IsGoal = false;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(MirrorHitInfo, StartPoint, EndPoint, ECC_GameTraceChannel6
		, Params);

	if (bHit)
	{
		FVector Hitpoint = MirrorHitInfo.Location;
		EndPoint = Hitpoint;
		NextMirror = Cast<ALaserMirror>(MirrorHitInfo.GetActor());

		//만약 충돌체가 목표 지점이라면
		AEndLaserPoint* Goal = Cast<AEndLaserPoint>(MirrorHitInfo.GetActor());
		if (Goal) { IsGoal = true; }
		
	}
	
	Lines.Add(EndPoint);

	if (NextMirror)
	{
		float dot = FVector::DotProduct(ReflectionVector, MirrorHitInfo.GetComponent()->GetRightVector());
		//UE_LOG(LogTemp, Warning, TEXT("%f"), dot);
		if (dot < 0)
		{
			NextMirror->NextLaserStart(MirrorHitInfo, ReflectionVector, LaserLength, Lines, IsGoal,IsReal);
		}		
	}

	if (bDrawLaser)
	{
		//확인용 디버그 라인
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red);
		DrawDebugLine(GetWorld(), StartPoint, StartPoint + SurfaceNormal * 500.0f, FColor::Black);
	}
}

//
//void ALaserMirror::StartGrab(AActor* HandActor)
//{
//	// HandActor에 부착
//	AttachToActor(HandActor, FAttachmentTransformRules::KeepWorldTransform);
//}
//
//void ALaserMirror::StopGrab(AActor* HandActor)
//{
//	// HandActor로부터 분리
//	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
//}
//
//void ALaserMirror::RotObject(const FRotator AddRotator)
//{
//	AddActorLocalRotation(AddRotator);
//}

bool ALaserMirror::IsGrab()
{
	return !IsGrabbing;
}

void ALaserMirror::StartGrab(UMotionControllerComponent* MontionComp, bool IsRight)
{
	//물리 및 콜리전 끄기
	MirrorMeshComp->SetSimulatePhysics(false);
	MirrorMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	//잡을려는 MotionController에게 붙이기
	MirrorMeshComp->AttachToComponent(MontionComp, FAttachmentTransformRules::KeepWorldTransform);
	//위치 손안으로
	//SetActorLocation(MontionComp->GetComponentLocation());
	IsGrabbing = true;
	IsComplete = false;
	OrginPos = GetActorLocation();

	SetActorRotation(FRotator());

	//스케일 축소 시키기
	if (!MoveToHandTimerHandle.IsValid())
	{
		HandComp = MontionComp;
		MoveToHandTimer = 0.0f;
		GetWorldTimerManager().SetTimer(MoveToHandTimerHandle, this,&ThisClass::MoveToHand, MoveToHandDeltatime, true);
	}

}

void ALaserMirror::StopGrab(UMotionControllerComponent* MontionComp, bool IsRight)
{
	IsGrabbing = false;
	MirrorMeshComp->SetSimulatePhysics(true);
	MirrorMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MirrorMeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	
	if (IsComplete)
	{
		IsComplete = false;
		TempMirroBoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TempMirrorMeshComp->SetVisibility(false);
		SetActorLocation(MovePos);
		SetActorRotation(TempMirrorMeshComp->GetComponentRotation());
	}

	if (MoveToHandTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(MoveToHandTimerHandle);
	}
	//스케일 원상복구
	if (!MoveToPlaceTimerHandle.IsValid())
	{
		HandComp = nullptr;
		GetWorldTimerManager().SetTimer(MoveToPlaceTimerHandle, this, &ThisClass::MoveToPlace, MoveToHandDeltatime, true);
	}


}

void ALaserMirror::OnButtonPressed(FHitResult& HitResult, EVRButton VRButton)
{
	if (!IsComplete)return;

	

}

void ALaserMirror::OnThumbstickValue(UMotionControllerComponent* MontionComp, bool IsRight, const FVector2D& Value)
{
	float AddYaw = 100 * Value.Y * GetWorld()->DeltaTimeSeconds;
	FRotator TempAddRot = FRotator(0, AddYaw, 0);
	TempMirrorRot(TempAddRot);
}



void ALaserMirror::UpdateScale()
{
	float percent = MoveToHandTimer / MoveToHandTime;
	//easeOutQuint
	if (bEaseOutQuint)
	{
		percent = 1 - FMath::Pow(1 - percent, 5);
	}

	float newScale = FMath::Lerp(OrginScale, MiniScale, percent);


	SetActorScale3D(FVector(newScale));
}

void ALaserMirror::MoveToHand() 
{
	MoveToHandTimer += MoveToHandDeltatime;
	if (MoveToHandTimer > MoveToHandTime)
	{
		SetActorScale3D(FVector(MiniScale));
		IsComplete = true;
		GetWorldTimerManager().ClearTimer(MoveToHandTimerHandle);
	}
	else
	{
		UpdateScale();
		//위치 이동
		float percent = MoveToHandTimer / MoveToHandTime;
	
		FVector offset = FVector(0.0f, 0.0f, -7.0f);
		FVector NewPos = FMath::Lerp(OrginPos, HandComp->GetComponentLocation(), percent);

		NewPos += offset;

		SetActorLocation(NewPos);
	}

}

void ALaserMirror::MoveToPlace()
{
	MoveToHandTimer -= MoveToHandDeltatime;
	if (MoveToHandTimer < 0)
	{
		SetActorScale3D(FVector(OrginScale));
		GetWorldTimerManager().ClearTimer(MoveToPlaceTimerHandle);
	}
	else
	{
		UpdateScale();
	}
}

void ALaserMirror::DrawTempMirror()
{
	if (!IsComplete) return;

	// 카메라의 위치와 방향 가져오기
	FVector StartLocation = HandComp->GetComponentLocation();
	FVector EndLocation = StartLocation + HandComp->GetForwardVector() * 10000.0f;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 자기 자신 무시
	QueryParams.AddIgnoredComponent(MirroBoxComp); // 콜리전 컴퍼넌트 무시
	QueryParams.AddIgnoredComponent(MirrorMeshComp); // 콜리전 컴퍼넌트 무시
	QueryParams.AddIgnoredComponent(TempMirrorMeshComp); // 콜리전 컴퍼넌트 무시
	QueryParams.AddIgnoredComponent(MirroBoxComp); //콜리전 컴퍼넌트 무시
	QueryParams.AddIgnoredComponent(TempMirroBoxComp); //콜리전 컴퍼넌트 무시

	// 라인트레이스 실행
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			EndLocation = HitResult.Location;
		
			TempMirroBoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			TempMirrorMeshComp->SetVisibility(true);
			TempMirrorMeshComp->SetWorldLocation(EndLocation);
			MovePos = EndLocation;
			MovePos.Z = 10.0f;
		}
	}
	else
	{
		TempMirroBoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TempMirrorMeshComp->SetVisibility(false);
		MovePos = GetActorLocation(); 
		MovePos.Z = 10.0f;
	}

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red);
	

}

void ALaserMirror::TempMirrorRot(FRotator AddRot)
{
	//FRotator 회전
	
	TempMirrorMeshComp->AddRelativeRotation(AddRot);
	
	//FQuat 회전
	//임시 회전 각도
	//float AddAngle = 10.0f;


}







