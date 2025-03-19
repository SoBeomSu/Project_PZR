// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_GameMode.h"
#include "SBS/SBS_GameState.h"

ASBS_GameMode::ASBS_GameMode()
{
	GameStateClass = ASBS_GameState::StaticClass();
}

int ASBS_GameMode::GetCoins() const
{
	return GetGameState<ASBS_GameState>()->CoinCount;
}

void ASBS_GameMode::SetCoins(int NewCoins)
{
	GetGameState< ASBS_GameState>()->CoinCount = NewCoins;
}
