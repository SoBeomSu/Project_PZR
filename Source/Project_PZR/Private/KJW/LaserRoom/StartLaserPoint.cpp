// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/LaserRoom/StartLaserPoint.h"

#include "Components/ArrowComponent.h"
#include "KJW/LaserRoom/LaserMirror.h"

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
	
}

// Called every frame
void AStartLaserPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector StartPoint = LaserArrowComp->GetComponentLocation();
	FVector LaserDir = LaserArrowComp->GetForwardVector();
	FVector EndPoint = StartPoint + (LaserDir * LaserLength);

	

	FHitResult HitInfo;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartPoint, EndPoint, ECC_GameTraceChannel1
		, Params);

	if (bHit)
	{
		FVector Hitpoint = HitInfo.Location;
		EndPoint = Hitpoint;

		if (ALaserMirror* Mirror = Cast<ALaserMirror>(HitInfo.GetActor()))
		{
			Mirror->NextLaserStart(HitInfo,LaserDir, LaserLength);
		}

	}

	SetBeamEnd(EndPoint);

	if (bStartLaser)
	{
		//확인용 디버그 라인
		DrawDebugLine(GetWorld(), LaserArrowComp->GetComponentLocation(), EndPoint, FColor::Red);

	}

}

void AStartLaserPoint::SetBeamEnd(FVector BeamEnd)
{
	if (NiagaraComp)
	{	
		NiagaraComp->Activate();
		NiagaraComp->SetVectorParameter(FName("Beam End"), BeamEnd);
	}
}

