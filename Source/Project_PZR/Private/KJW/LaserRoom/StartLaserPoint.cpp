// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/LaserRoom/StartLaserPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"
#include "KJW/LaserRoom/LaserMirror.h"

#include "KJW/LaserRoom/LaserRoomGameMode.h"
#include "KJW/LaserRoom/EndLaserPoint.h"
#include "KJW/LaserRoom/Laser.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"


// Sets default values
AStartLaserPoint::AStartLaserPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaserComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserComp"));
	SetRootComponent(LaserComp);

	LaserArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("LaserArrowComp"));
	LaserArrowComp->SetupAttachment(RootComponent);

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetupAttachment(LaserArrowComp);

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
void AStartLaserPoint::BeginPlay()
{
	Super::BeginPlay();
	LRGM = Cast<ALaserRoomGameMode>(GetWorld()->GetAuthGameMode());
	ensure(LRGM);

	IsGoal = false;
}

void AStartLaserPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ReturnLaser();

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AStartLaserPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LaserDelayTimer < LaserDelay)
	{
		LaserDelayTimer += DeltaTime;
		return;
	}

	LaserDelayTimer = 0.0f;
	//StartLaser();
	//1. 레이저 쏘기
	StartSetLaser();
	//2. 라인정보를 가지고 레이저 그리기
	DrawLaser();
	
	//3. 최종 목적지에 도달 했는지
	CheckIsGoalLaser();

}

void AStartLaserPoint::StartSetLaser()
{
	//레이저 쏘기전 필요한 초기화
	Lines.Empty();
	IsGoal = false;

	//1.시작 위치 방향 조절
	FVector StartPoint = LaserArrowComp->GetComponentLocation();
	FVector LaserDir = LaserArrowComp->GetForwardVector();
	FVector EndPoint = StartPoint + (LaserDir * LaserLength);
	
	Lines.Add(StartPoint);

	//2. 레이저 충돌 찾기
	FHitResult HitInfo;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartPoint, EndPoint, ECC_GameTraceChannel1
		, Params);
	
	ALaserMirror* Mirror = nullptr;
	
	//2 - 1충돌이 있다면 -> 그것이 거울인지 확인 하기
	if (bHit)
	{
		FVector Hitpoint = HitInfo.Location;
		EndPoint = Hitpoint;	
		Mirror = Cast<ALaserMirror>(HitInfo.GetActor());
	}

	Lines.Add(EndPoint);
	//2 - 2만약 거울이라면 다음 레이저 쏘기
	if (Mirror)
	{
		Mirror->NextLaserStart(HitInfo, LaserDir, LaserLength, Lines, IsGoal);
	}


	if (bDrawLaser)
	{
		//확인용 디버그 라인
		DrawDebugLine(GetWorld(), LaserArrowComp->GetComponentLocation(), EndPoint, FColor::Red);
	}

}

void AStartLaserPoint::DrawLaser()
{
	if (Lines.Num() < 2) { return; }
	
	FVector StartPoint = Lines[0];
	FVector EndPoint = Lines[1];
	int32 NeedLaser = Lines.Num();

	GetLaser(NeedLaser);

	for (int i = 1; i < NeedLaser; ++i)
	{
		EndPoint = Lines[i];
		ALaser* DrawLaser = Lasers[i];
		DrawLaser->SetBeamEnd(StartPoint , EndPoint);
		StartPoint = EndPoint;
	}

}

void AStartLaserPoint::GetLaser(int32 Count)
{
	if (Lasers.Num() == Count) { return;}

	if (!Lasers.IsEmpty()) { ReturnLaser(); }

	for (int32 i = 0; i < Count; ++i)
	{
		Lasers.Add(LRGM->GetLaser());
	}
}

void AStartLaserPoint::ReturnLaser()
{
	for (int32 i = 0; i < Lasers.Num(); ++i)
	{
		LRGM->ReturnLaser(Lasers[i]);
	}
	
	Lasers.Empty();
}

void AStartLaserPoint::CheckIsGoalLaser()
{
	if (!CurentEndLaserPoint)
	{
		CurentEndLaserPoint =
			Cast<AEndLaserPoint>( UGameplayStatics::GetActorOfClass(GetWorld() , AEndLaserPoint::StaticClass()));
	}

	if (!CurentEndLaserPoint) { return; }

	if (IsGoal)
	{
		CurentEndLaserPoint->AddMirrorPoint(this);
	}
	else
	{
		CurentEndLaserPoint->RemoveMirrorPoint(this);
	}
}

