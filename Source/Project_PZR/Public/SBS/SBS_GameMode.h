// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SBS_LightSwitch.h"
#include "SBS_Bomb.h"
#include "SBS_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PZR_API ASBS_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	ASBS_GameMode();
	virtual ~ASBS_GameMode() = default;

	//TArray<A
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bStartGame = false;
	
	bool Phase2 = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGameOver = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGameClear = false;
	UPROPERTY(EditAnywhere)
	bool bPasswordCorrect = false;
	UPROPERTY(EditAnywhere)
	bool bSwitchCorrect = false;
	UPROPERTY(EditAnywhere)
	bool bAnimalCorrect = false;
	UPROPERTY(EditAnywhere)
	int CorrectCount = 0;

	TArray<ASBS_LightSwitch*> Switches;
	TArray<bool> CorrectPattern = { true, false, true, false, false, true, false, true };
	ASBS_Bomb* Bomb;


	void UpdateAnimalCount(int Animalcount);
	int AnimalInSafe;
	const int RequireAnimal = 5;


	void UpdateGameState();

	void SetPasswordCorrect(bool bValue);
	void SetSwitchCorrect(bool bValue);
	void SetAnimalCorrect(bool bValue);

	void StartGame();
	void GameOver();
	void Congraturation();


};