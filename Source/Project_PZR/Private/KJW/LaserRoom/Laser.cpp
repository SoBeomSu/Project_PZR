// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/Laser.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComp =  CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(SceneComp);

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
void ALaser::BeginPlay()
{
	Super::BeginPlay();
	
}



void ALaser::SetBeamEnd(FVector StartPoint, FVector EndPoint)
{
	if (NiagaraComp)
	{
		if (!NiagaraComp->IsActive())
		{
			NiagaraComp->Activate();
		}
		NiagaraComp->SetWorldLocation(StartPoint);
		NiagaraComp->SetVectorParameter(FName("Beam End"), EndPoint);
	}
}

void ALaser::ResetBeam()
{
	if (NiagaraComp)
	{
		if (NiagaraComp->IsActive())
		{
			NiagaraComp->DeactivateImmediate();
		}
	}

}

