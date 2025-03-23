// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/QPuzzle/QPDisplay.h"
#include "KJW/QPuzzle/QPuzzleGameMode.h"
#include "KJW/QPuzzle/QPuzzleData.h"

#include "Components/TextBlock.h"



void UQPDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	ChoiceTexts.Add(ATextBlock);
	ChoiceTexts.Add(BTextBlock);
	ChoiceTexts.Add(CTextBlock);
	ChoiceTexts.Add(DTextBlock);

	HideAllDisplay();

	StateInfoTextBlock->SetVisibility(ESlateVisibility::Visible);
	StateInfoTextBlock->SetText(FText::FromString("Ready..."));
}

void UQPDisplay::SetDisplay(EKGameState LaserGameState)
{
	HideAllDisplay();

	if (LaserGameState == EKGameState::START)
	{
		SetQPuzzle();
		
	}
	else if (LaserGameState == EKGameState::FINISH)
	{
		StateInfoTextBlock->SetVisibility(ESlateVisibility::Visible);
		StateInfoTextBlock->SetText(FText::FromString("CLEAR..."));
	}

}

void UQPDisplay::SetAnswerText(FText text)
{
	MyAnwserTextBlock->SetVisibility(ESlateVisibility::Visible);
	MyAnwserTextBlock->SetText(text);
}

void UQPDisplay::HideAllDisplay()
{
	MainDescTextBlock->SetVisibility(ESlateVisibility::Hidden);
	SubDescTextBlock->SetVisibility(ESlateVisibility::Hidden);
	MyAnwserTextBlock->SetVisibility(ESlateVisibility::Hidden);
	AnswerTextBlock->SetVisibility(ESlateVisibility::Hidden);

	for (UTextBlock* Choicetext : ChoiceTexts)
		Choicetext->SetVisibility(ESlateVisibility::Hidden);
	
	StateInfoTextBlock->SetVisibility(ESlateVisibility::Hidden);
	
}

void UQPDisplay::SetQPuzzle()
{
	if (!QPGM) return;

	UQPuzzleData* data = QPGM->GetPuzzleData();
	if (!data) return;

	AnswerTextBlock->SetVisibility(ESlateVisibility::Visible);
	MainDescTextBlock->SetVisibility(ESlateVisibility::Visible);
	SubDescTextBlock->SetVisibility(ESlateVisibility::Visible);
	
	MainDescTextBlock->SetText(data->MainDesc);
	SubDescTextBlock->SetText(data->SubDesc);

	int32 ChoiseNum = data->ChoiceNumber;
	for (int32 i = 0; i < ChoiseNum; ++i)
	{
		UTextBlock* ChoiseText = ChoiceTexts[i];
		ChoiseText->SetVisibility(ESlateVisibility::Visible);
		ChoiseText->SetText(data->ChoicesText[i]);
	}


}
