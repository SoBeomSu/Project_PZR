// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_GameMode.h"
#include "SBS/SBS_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "SBS/SBS_LightSwitch.h"

ASBS_GameMode::ASBS_GameMode()
{
	GameStateClass = ASBS_GameState::StaticClass();

	TArray<AActor*> LightSwitch;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASBS_LightSwitch::StaticClass(), LightSwitch);
	for (AActor* Actor : LightSwitch)
	{
		Switches.Add(Cast<ASBS_LightSwitch>(Actor));
	}
	AActor* castBomb = UGameplayStatics::GetActorOfClass(GetWorld(), ASBS_Bomb::StaticClass());
	Bomb = Cast<ASBS_Bomb>(castBomb);

}
void ASBS_GameMode::StartGame()
{
	bStartGame = true;
	TArray<AActor*> FoundActors;
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyActor::StaticClass(), FoundActors);
}

void ASBS_GameMode::UpdateAnimalCount(int Animalcount)
{
	AnimalInSafe +=Animalcount;
	UE_LOG(LogTemp, Log, TEXT("AnimalCout %d"),AnimalInSafe);
	if (AnimalInSafe >= RequireAnimal)
	{
		SetAnimalCorrect(true);
	}
}

void ASBS_GameMode::SetPasswordCorrect(bool bValue)
{
	bPasswordCorrect = bValue;
	UpdateGameState();
	//UE_LOG(LogTemp, Log, TEXT("Pattern Incorrect"));

}	

void ASBS_GameMode::SetSwitchCorrect(bool bValue)
{
	if (Switches.Num() != CorrectPattern.Num()) return;

	Switches.Sort([](const ASBS_LightSwitch& A, const ASBS_LightSwitch& B)
	{
		return A.SwitchID < B.SwitchID;  
	});

	bool bPatternCorrect = true;
	for (int32 i = 0; i < Switches.Num(); i++)
	{
		if (Switches[i]->bIsOn != CorrectPattern[i])
		{
			bPatternCorrect = false;
			break;
		}
	}
	if (bPatternCorrect)
	{
		bSwitchCorrect = true;
		UE_LOG(LogTemp, Log, TEXT("Pattern Correct"));

		UpdateGameState();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Pattern Incorrect"));
	}
}

void ASBS_GameMode::SetAnimalCorrect(bool bValue)
{
	bAnimalCorrect = bValue;
	UpdateGameState();
}


void ASBS_GameMode::UpdateGameState()
{	
	int CorrectCount = 0;
	if(bPasswordCorrect) CorrectCount++;
	if(bSwitchCorrect) CorrectCount++;
	if(bAnimalCorrect) CorrectCount++;

	if (Bomb)
	{
		Bomb->UpdateBombMaterial(CorrectCount);
	}

	if (bPasswordCorrect && bAnimalCorrect && bSwitchCorrect)
	{
		Congraturation();
		UE_LOG(LogTemp, Log, TEXT("Game Clear"));
	}
}

void ASBS_GameMode::Congraturation()
{
	bGameClear = true;
}

void ASBS_GameMode::GameOver()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("TempLevel"));
}
