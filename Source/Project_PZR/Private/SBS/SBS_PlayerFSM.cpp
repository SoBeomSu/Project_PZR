// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_PlayerFSM.h"

// Sets default values for this component's properties
USBS_PlayerFSM::USBS_PlayerFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USBS_PlayerFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USBS_PlayerFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	switch (mState)
	{
	case ESBSPlayerState::Idle: IdleState(); break;
	case ESBSPlayerState::Move: MoveState(); break;
	case ESBSPlayerState::Grab: GrabState(); break;

	}
}

void USBS_PlayerFSM::IdleState()
{

}

void USBS_PlayerFSM::MoveState()
{

}

void USBS_PlayerFSM::GrabState()
{
	
}

