// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "SBS_WorldLightManager.h"
#include "SBS_LightSwitch.generated.h"

UCLASS()
class PROJECT_PZR_API ASBS_LightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBS_LightSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* SwitchMesh;

	UPROPERTY(EditAnywhere)
	class USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere)
	ASBS_WorldLightManager* WorldLight;

	float CurrentTime = 0;
	bool bCanGrap = true;
	bool bIsOn = false;
	float ResetTime = 0;
	float StartAngle = 0;
	bool bIsResetting = false;

	UPROPERTY(EditDefaultsOnly)
	float SwitchOffTime = 5;
	UPROPERTY(EditDefaultsOnly)
	float ResetDuration = 10;


	void SetSwitchRotation(float SwitchRotate);
	void StartReset();
	void ResetRotation(float Deltatime);
	void SwitchOn();
	void SwitchOff();
};
