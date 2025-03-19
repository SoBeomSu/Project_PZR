// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SBS_GameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PZR_API ASBS_GameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ASBS_GameState();
	virtual ~ASBS_GameState() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CoinCount;
};
