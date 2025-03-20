// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_Animal.h"
#include "SBS/SBS_AnimalFSM.h"

// Sets default values
ASBS_Animal::ASBS_Animal()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionProfileName("GrapObject");

	AnimalFSM = CreateDefaultSubobject<USBS_AnimalFSM>(TEXT("FSMcomp"));
}

// Called when the game starts or when spawned
void ASBS_Animal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBS_Animal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASBS_Animal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

