// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KJW/KHelper.h"
#include "LaserRoomGameMode.generated.h"

/**
 * 
 */



DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateDelegate, ELaserGameState);

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
	//레이저 풀 관련
	void SpawnLaser();
	//레이저 주기
 	class ALaser* GetLaser();
	//레이저 돌려받는 
	void ReturnLaser(class ALaser* Laser);

	int32 GetCurentStage() { return Stage; }
	void SetDisplayGmae(class  ALRStatgeDisplay* NewDisplay) { Display = NewDisplay; };
private:
	void SetDisplay();
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
	FTimerHandle LaserGameStateTimerHandle;
public:
	FUpdateDelegate UpdateStageDelegate;
private:
	UPROPERTY()
	TArray<AActor*> SpawnedActors;

	//스폰용 레이저 이펙트 클래스
	UPROPERTY(EditAnywhere, Category = "Laser_Effects" , meta = (AllowPrivateAccess = true))
	TSubclassOf<class ALaser> LaserClass;
	TQueue<class ALaser*> LaserPool;

private:
	class ALRStatgeDisplay* Display;

};
