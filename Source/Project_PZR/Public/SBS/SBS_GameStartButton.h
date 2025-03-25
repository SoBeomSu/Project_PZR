// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBS_GameMode.h"
#include "SBS_LightSwitch.h"
#include "SBS_GameStartButton.generated.h"

UCLASS()
class PROJECT_PZR_API ASBS_GameStartButton : public AActor, public IKVRObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBS_GameStartButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Pillar;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Button;

	void ButtonPressed();

	ASBS_GameMode* GameMode01;
	ASBS_LightSwitch* Lightswitch;

	float DelayTime;
	bool bworked = false;
	virtual bool  IsGrab() override { return true; };
	virtual void StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
};
