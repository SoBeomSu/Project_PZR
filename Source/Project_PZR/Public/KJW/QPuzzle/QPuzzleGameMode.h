// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KJW/KHelper.h"
#include "QPuzzleGameMode.generated.h"

/**
 * 
 */


DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateDelegate, EKGameState);

UCLASS()
class PROJECT_PZR_API AQPuzzleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	AQPuzzleGameMode();
protected:
	virtual void BeginPlay() override;

public:
	//게임 상태 변경
	void ChangeLaserGameState(EKGameState NewLaserGameState);
	
	//퍼즐 변경하기
	bool ChangeQPuzzle();

public:
	class UQPuzzleData* GetPuzzleData() { return CurQPuzzleData; }

private :
	void InitPuzzleDatas();

public:
	FUpdateDelegate UpdateStageDelegate;
private:
	EKGameState QPuzzleGameState = EKGameState::NONE;


	UPROPERTY(EditAnywhere, Category = "QPuzzleData", meta = (AllowPrivateAccess = true))
	TArray<class UQPuzzleData*> QPuzzleDatas;

	//중복방지용
	TArray<int32> QPuzzleIndex;
	class UQPuzzleData* CurQPuzzleData;

	UPROPERTY(VisibleAnywhere)
	int32 PuzzleCount = 0;

	UPROPERTY(EditAnywhere , Category = "QPuzzleData", meta = (AllowPrivateAccess = true))
	int32 GoalCount = 0;


	FTimerHandle QPuzzleGameStateTimerHandle;

};
