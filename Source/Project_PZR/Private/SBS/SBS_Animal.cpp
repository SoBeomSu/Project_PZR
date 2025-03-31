// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_Animal.h"
#include "SBS/SBS_AnimalFSM.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MotionControllerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SBS/SBS_GameMode.h"

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
	TArray<AActor*> SafeZones;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("SafeZone"), SafeZones);
	if (SafeZones.Num() > 0)
	{
		SafeZones[0]->OnActorBeginOverlap.AddDynamic(this, &ASBS_Animal::OnSafeZoneOverlap);
		SafeZones[0]->OnActorEndOverlap.AddDynamic(this, &ASBS_Animal::OnSafeZoneEndOverlap);
	}
	if(bIsLeader)
		SkeletalMesh->SetMaterial(0, YellowDuck);
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


void ASBS_Animal::OnSafeZoneOverlap(AActor* OVerlappedActor, AActor* OtherActor)
{
	if (OtherActor == this)
	{
		bInSafeZone = true;
		ASBS_GameMode* GM = Cast<ASBS_GameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->UpdateAnimalCount(1);  // 카운터 증가
			UE_LOG(LogTemp, Warning, TEXT("Counter Up"));

		}
	}
}

void ASBS_Animal::OnSafeZoneEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == this)
	{
		bInSafeZone = false;
		ASBS_GameMode* GM = Cast<ASBS_GameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->UpdateAnimalCount(-1);  // 카운터 감소
			UE_LOG(LogTemp, Warning, TEXT("Counter Down"));

		}
	}
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
	BoxComp->AddImpulse(ThrowPower*ThrowDirection, NAME_None, true);
	AnimalFSM->SetState(ESBS_AnimalState::Idle);
	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//UE_LOG(LogTemp, Warning, TEXT("Animal Release"));
}

void ASBS_Animal::Grabbing(class UMotionControllerComponent* MontionComp, bool IsRight)
{
	ThrowDirection = MontionComp->GetComponentLocation() - PrePos;

	//회전변화량 구하기
	//공식
	//anlge1 = Q1, angle2 = Q2
	//angle1 + angle2 = Q1 + Q2
	//~angel2 = Q2.inverse()
	//angle2 - anlge1 = angle2+ (-angle1) = Q2 * Q1.inverse()

	DeltaRotation = MontionComp->GetComponentQuat() * PreRot.Inverse();

	PrePos = MontionComp->GetComponentLocation();
	PreRot = MontionComp->GetComponentQuat();
}