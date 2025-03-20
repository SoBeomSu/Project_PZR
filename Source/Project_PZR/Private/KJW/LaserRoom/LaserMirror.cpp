// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/LaserRoom/LaserMirror.h"
#include "KJW/KHelper.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"


#include "KJW/LaserRoom/EndLaserPoint.h"
// Sets default values
ALaserMirror::ALaserMirror()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	SetRootComponent(BoxComp);

	MirrorComp = CreateDefaultSubobject<UStaticMeshComponent>("MirrorComp");
	MirrorComp->SetupAttachment(RootComponent);

	MirrorArrowComp = CreateDefaultSubobject<UArrowComponent>("MirrorArrowComp");
	MirrorArrowComp->SetupAttachment(MirrorComp);

	BottomComp = CreateDefaultSubobject<UStaticMeshComponent>("BottomComp");
	BottomComp->SetupAttachment(RootComponent);
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mirror(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (Mirror.Succeeded()) MirrorComp->SetStaticMesh(Mirror.Object);

	ConstructorHelpers::FObjectFinder<UStaticMesh> Bottom(TEXT("/Script/Engine.StaticMesh'/Engine/VREditor/LaserPointer/CursorPointer.CursorPointer'"));
	if (Bottom.Succeeded()) BottomComp->SetStaticMesh(Bottom.Object);

	BoxComp->SetBoxExtent(FVector(50.0f, 6.5f, 70.0f));

	MirrorComp->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	MirrorComp->SetRelativeScale3D(FVector(1.0f, 0.1f, 1.0f));

	MirrorArrowComp->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));
	MirrorArrowComp->SetRelativeRotation(FRotator(0.0, 90.0f, 0.0f));

	BottomComp->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
	BottomComp->SetRelativeScale3D(FVector(0.5f, 0.2f, 0.2f));
	BottomComp->SetRelativeRotation(FRotator(90.0f,0.0f, 0.0f));


	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/A_Project/KJW/LaserRoom/Actor/NS_Beam.NS_Beam'")
	);

	if (NiagaraSystemAsset.Succeeded())
	{
		NiagaraComp->SetAsset(NiagaraSystemAsset.Object);
	}

	NiagaraComp->bAutoActivate = false;  // 처음엔 꺼둠, 필요할 때 실행
}

// Called when the game starts or when spawned
void ALaserMirror::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserMirror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALaserMirror::NextLaserStart(const FHitResult& HitInfo, const FVector& InDir, const float& LaserLength)
{
	FVector SurfaceNormal = HitInfo.ImpactNormal;

	FVector StartPoint = HitInfo.Location;
	FVector ReflectionVector = KHelper::GetReflectionVector(InDir, SurfaceNormal);
	//FVector ReflectionVector = InDir.MirrorByVector(SurfaceNormal);
	FVector EndPoint = StartPoint + (ReflectionVector * LaserLength);

	FHitResult MirrorHitInfo;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(MirrorHitInfo, StartPoint, EndPoint, ECC_GameTraceChannel1
		, Params);

	if (bHit)
	{
		FVector Hitpoint = MirrorHitInfo.Location;
		EndPoint = Hitpoint;

		

		if (ALaserMirror* Mirror = Cast<ALaserMirror>(MirrorHitInfo.GetActor()))
		{
			Mirror->NextLaserStart(MirrorHitInfo, ReflectionVector, LaserLength);
		}
		else if(AEndLaserPoint* Goal = Cast<AEndLaserPoint>(MirrorHitInfo.GetActor()))
		{
			EndLaserPoint = Goal;
			Goal->SetLaserSucceed(true);
		}

		SetBeamEnd(StartPoint, EndPoint);
	}
	
	if (EndLaserPoint.IsValid() && !bHit)
	{
		EndLaserPoint->SetLaserSucceed(false);
		EndLaserPoint = nullptr;
	}
	

	if (bStartLaser)
	{
		//확인용 디버그 라인
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red);
		DrawDebugLine(GetWorld(), StartPoint, StartPoint +  SurfaceNormal* 500.0f, FColor::Black);
	}
}

void ALaserMirror::StartGrab(AActor* HandActor)
{
	// HandActor에 부착
	AttachToActor(HandActor, FAttachmentTransformRules::KeepWorldTransform);
}

void ALaserMirror::StopGrab(AActor* HandActor)
{
	// HandActor로부터 분리
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void ALaserMirror::RotObject(const FRotator AddRotator)
{
	AddActorLocalRotation(AddRotator);
}

void ALaserMirror::SetBeamEnd(FVector StartPoint, FVector EndPoint)
{
	if (NiagaraComp)
	{
		NiagaraComp->Activate();
		NiagaraComp->SetWorldLocation(StartPoint);
		NiagaraComp->SetVectorParameter(FName("Beam End"), EndPoint);
	}
}





