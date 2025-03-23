// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LRDisplay.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "KJW/LaserRoom/LaserRoomGameMode.h"

#include "Kismet/GameplayStatics.h"



void ULRDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	ToBackButton->OnClicked.AddDynamic(this, &ThisClass::ToBackFunc);

	ToBackButton->SetVisibility(ESlateVisibility::Hidden);
}

void ULRDisplay::ToBackFunc()
{
	FName LevelName = TEXT("TempLevel");
	UGameplayStatics::OpenLevel(this, LevelName);
}

void ULRDisplay::SetDisplay(EKGameState LaserGameState)
{
	if (!LRGM) return;

	int32 curStage = LRGM->GetCurentStage();

	if (LaserGameState == EKGameState::FINISH)
	{
		MainTextBlock->SetText(FText::FromString("FINISH..."));
		ToBackButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		FString str = FString::Printf(TEXT("Stage - %d"), curStage);
		MainTextBlock->SetText(FText::FromString(str));
		ToBackButton->SetVisibility(ESlateVisibility::Hidden);
	}
}
