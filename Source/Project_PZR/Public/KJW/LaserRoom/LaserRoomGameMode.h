// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LaserRoomGameMode.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ELaserGameState : uint8
{
	NONE UMETA(DisplayName = "None"),
	START UMETA(DisplayName = "Start"),
	INGAME UMETA(DisplayName = "InGame"),
	CLEAR UMETA(DisplayName = "Clear"),
	FINISH UMETA(DisplayName = "Finish"),
};

UCLASS()
class PROJECT_PZR_API ALaserRoomGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	ALaserRoomGameMode();
protected:
	virtual void BeginPlay() override;

public:
	//게임 상태 변경
	void ChangeLaserGameState(ELaserGameState NewLaserGameState);
	//현제 스테이지 액터 스폰
	void SpawnStageActor();
	//스폰된 액터 제거
	void ResetStageActor();

public:
	UPROPERTY(EditAnywhere, Category = "LaserStageDatas")
	ELaserGameState LaserGameState = ELaserGameState::NONE;
	UPROPERTY(EditAnywhere, Category = "LaserStageDatas")
	int32 NeedLaser = 1;
private:
	UPROPERTY(EditAnywhere, Category = "LaserStageDatas" , meta = (AllowPrivateAccess = true))
	TArray<class ULaserStageData*> StageDatas;

	UPROPERTY(EditAnywhere, Category = "LaserStageDatas", meta = (AllowPrivateAccess = true))
	int32 Stage = 1;

	UPROPERTY(EditAnywhere, Category = "LaserStageDatas", meta = (AllowPrivateAccess = true))
	int32 MaxStage = 1;

private:
	UPROPERTY()
	TArray<AActor*> SpawnedActors;





};
