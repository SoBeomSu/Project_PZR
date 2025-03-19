// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SBS_PlayerC.generated.h"

UCLASS()
class PROJECT_PZR_API ASBS_PlayerC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASBS_PlayerC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
