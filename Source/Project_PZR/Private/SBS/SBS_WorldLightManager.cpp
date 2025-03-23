// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_WorldLightManager.h"
#include "Components/SpotLightComponent.h"

// Sets default values
ASBS_WorldLightManager::ASBS_WorldLightManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetVisibility(true);
}

// Called when the game starts or when spawned
void ASBS_WorldLightManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBS_WorldLightManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


