// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_FirePit.h"
#include "SBS/SBS_Animal.h"
#include "Components/SphereComponent.h"
#include "../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "SBS/SBS_AnimalFSM.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASBS_FirePit::ASBS_FirePit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	FireNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireNiagara"));
	FireNiagara->SetupAttachment(SphereCollision);
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticle"));
	ParticleSystem->SetupAttachment(SphereCollision);
}

// Called when the game starts or when spawned
void ASBS_FirePit::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ASBS_FirePit::FireOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ASBS_FirePit::FireOverlapEnd);

}

// Called every frame
void ASBS_FirePit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBS_FirePit::FireOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASBS_Animal* OverlapAnimal = Cast<ASBS_Animal>(OtherActor);
	if (OverlapAnimal)
	{
		OverlapAnimal->AnimalFSM->SetState(ESBS_AnimalState::Burning);
	}
}

void ASBS_FirePit::FireOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASBS_Animal* OverlapAnimal = Cast<ASBS_Animal>(OtherActor);
	if (OverlapAnimal)
	{
		OverlapAnimal->AnimalFSM->SetState(ESBS_AnimalState::Idle);
	}
}

