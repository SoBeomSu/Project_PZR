// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_GameStartButton.h"

// Sets default values
ASBS_GameStartButton::ASBS_GameStartButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASBS_GameStartButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBS_GameStartButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

