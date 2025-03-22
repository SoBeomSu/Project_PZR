// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LRDisplay.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "KJW/LaserRoom/LaserRoomGameMode.h"

#include "Kismet/GameplayStatics.h"


void ULRDisplay::SetDisplay(ELaserGameState LaserGameState)
{
	if (!LRGM) return;

	int32 curStage = LRGM->GetCurentStage();

	if (LaserGameState == ELaserGameState::FINISH)
	{
		MainTextBlock->SetText(FText::FromString("FINISH..."));
	}
	else
	{
		FString str = FString::Printf(TEXT("Stage - %d"), curStage);
		MainTextBlock->SetText(FText::FromString(str));
	}
}

void ULRDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	ToBackButton->OnClicked.AddDynamic(this, &ThisClass::ToBackFunc);
}

void ULRDisplay::ToBackFunc()
{
	FName LevelName = TEXT("TestLevel");
	UGameplayStatics::OpenLevel(this, LevelName);
}

