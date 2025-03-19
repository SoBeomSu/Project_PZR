// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartLaserPoint.generated.h"

UCLASS()
class PROJECT_PZR_API AStartLaserPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStartLaserPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* LaserComp;
	
	UPROPERTY(EditAnywhere)
	class UArrowComponent* LaserArrowComp;

public:
	UPROPERTY(EditAnywhere, Category = "StartLaser")
	bool bStartLaser = false;

public:
	UPROPERTY(EditAnywhere , Category = "StartLaser")
	float LaserLength = 1000.0f;



};
