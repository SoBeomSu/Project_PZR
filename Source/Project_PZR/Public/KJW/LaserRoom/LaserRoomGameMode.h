// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LaserRoomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PZR_API ALaserRoomGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	ALaserRoomGameMode();
	
public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "LaserStageDatas")
	TArray<class ULaserStageData*> StageDatas;

	UPROPERTY(EditAnywhere, Category = "LaserStageDatas")
	int32 Stage = 1;

	void SpawnStageActor();
	void ResetStageActor();
	
	UPROPERTY()
	TArray<AActor*> SpawnedActors;
};
