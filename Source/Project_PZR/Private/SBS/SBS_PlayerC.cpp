// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_PlayerC.h"

// Sets default values
ASBS_PlayerC::ASBS_PlayerC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASBS_PlayerC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBS_PlayerC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASBS_PlayerC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

