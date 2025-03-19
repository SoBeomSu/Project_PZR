// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

	UFUNCTION(BlueprintPure,Category="Coins")
	virtual int GetCoins() const;

	UFUNCTION(BlueprintCallable,Category="Coins")
	virtual void SetCoins(int NewCoins);
};