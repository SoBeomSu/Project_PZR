// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_AnimalFSM.h"
#include "SBS/SBS_Animal.h"
#include "SBS/SBS_FirePit.h"
#include "Kismet/GameplayStatics.h"
#include "SBS/SBS_GameMode.h"
#include "MotionControllerComponent.h"

// Sets default values for this component's properties
USBS_AnimalFSM::USBS_AnimalFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USBS_AnimalFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GameMode = Cast<ASBS_GameMode>(GetWorld()->GetAuthGameMode());
	Animal = Cast<ASBS_Animal>(GetOwner());

}


// Called every frame
void USBS_AnimalFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	switch (mState)
	{
	case ESBS_AnimalState::Stay: Stay(DeltaTime); break;
	case ESBS_AnimalState::Idle: IdleState(); break;
	case ESBS_AnimalState::Move: MoveState(); break;
	case ESBS_AnimalState::InAir: InAir(); break;
	case ESBS_AnimalState::Burning: Burning(); break;
	case ESBS_AnimalState::Dead: Dead(); break;
	}
}

void USBS_AnimalFSM::Stay(float Deltatime)
{
	if(GameMode->Phase2)
	{
		CurrentTime += Deltatime;
		if(CurrentTime > 3)
		{
			SetState(ESBS_AnimalState::Idle);
		}
	}
}

void USBS_AnimalFSM::IdleState()
{
	//Animal->BoxComp->UPrimitiveComponent::SetSimulatePhysics(true);
	Animal->SkeletalMesh->SetVisibility(true);
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= StayTime)
	{
		CurrentTime = 0;
		SetState(ESBS_AnimalState::Move);
	}
}

void USBS_AnimalFSM::MoveState()
{
	if (Animal)
	{
		FVector CurrentAnimalLocation = Animal->GetActorLocation();
		Firepit = Cast<ASBS_FirePit>(UGameplayStatics::GetActorOfClass(GetWorld(), ASBS_FirePit::StaticClass()));
		if (Firepit)
		{
			AnimalDir = Firepit->GetActorLocation() - Animal->GetActorLocation();
			AnimalDir.Z = 0;
			AnimalDir.Normalize();
		}
		else
			AnimalDir = Animal-> GetActorForwardVector();

		Animal->SetActorLocation(CurrentAnimalLocation + AnimalDir*AnimalSpeed*GetWorld()->GetDeltaSeconds());
		Animal->SetActorRotation(FRotator(0, AnimalDir.Rotation().Yaw, -90));
	}
}

void USBS_AnimalFSM::InAir()
{
	//if (CurrentTime > StayTime)
	//{
	//	SetState(ESBS_AnimalState::Idle);
	//}
}

void USBS_AnimalFSM::Burning()
{
	AnimalHealth = Animal->Health;
	Firepit = Cast<ASBS_FirePit>(GetOwner());
	float CurrentTime2 = 0;
	if (CurrentTime2 > BurnTime)
	{
		AnimalHealth -= Firepit->FireDamage;
		CurrentTime2 = 0;
		if (AnimalHealth <= 0)
		{
			SetState(ESBS_AnimalState::Dead);
			GameMode->GameOver();
		}
	}
}

void USBS_AnimalFSM::Dead()
{
	
}



