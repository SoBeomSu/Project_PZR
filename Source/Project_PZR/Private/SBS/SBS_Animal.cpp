// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_Animal.h"
#include "SBS/SBS_AnimalFSM.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MotionControllerComponent.h"

// Sets default values
ASBS_Animal::ASBS_Animal()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetCollisionProfileName("GrapObject");
	BoxComp->SetSimulatePhysics(true);
	RootComponent = BoxComp;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMesh"));
	SkeletalMesh->SetupAttachment(BoxComp);
	SkeletalMesh->SetVisibility(false);

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


void ASBS_Animal::StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight)
{
	BoxComp->SetSimulatePhysics(false);
	AnimalFSM->SetState(ESBS_AnimalState::InAir);
	this->AttachToComponent(MontionComp, FAttachmentTransformRules::KeepWorldTransform);
	
	UE_LOG(LogTemp, Warning, TEXT("Animal Grab"));
}

void ASBS_Animal::StopGrab(class UMotionControllerComponent* MontionComp, bool IsRight)
{
	BoxComp->SetSimulatePhysics(true);
	AnimalFSM->SetState(ESBS_AnimalState::Idle);
	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	UE_LOG(LogTemp, Warning, TEXT("Animal Release"));
}

void ASBS_Animal::Grabbing(class UMotionControllerComponent* MontionComp, bool IsRight)
{

}