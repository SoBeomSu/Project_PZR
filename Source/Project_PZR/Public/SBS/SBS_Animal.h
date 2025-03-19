// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SBS_Animal.generated.h"

UCLASS()
class PROJECT_PZR_API ASBS_Animal : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASBS_Animal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

};
