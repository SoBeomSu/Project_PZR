// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_AnimalFSM.h"
#include "SBS/SBS_Animal.h"

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
	Animal = Cast<ASBS_Animal>(GetOwner());
}


// Called every frame
void USBS_AnimalFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	switch (mState)
	{
	case ESBS_AnimalState::Idle: IdleState(); break;
	case ESBS_AnimalState::Move: MoveState(); break;
	}
}

void USBS_AnimalFSM::IdleState()
{
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= StayTime)
	{
		CurrentTime = 0;
		//SetState(ESBS_AnimalState::Move);
	}

}

void USBS_AnimalFSM::MoveState()
{
	if (Animal)
	{
		FVector CurrentAnimalLocation = Animal->GetActorLocation();
		AnimalDir = Animal->GetActorForwardVector();
		Animal->SetActorLocation(CurrentAnimalLocation + AnimalDir*AnimalSpeed*GetWorld()->GetDeltaSeconds());
	}
}

void USBS_AnimalFSM::InAir()
{
	CurrentTime =0;
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > StayTime)
	{
		SetState(ESBS_AnimalState::Idle);
	}
}

