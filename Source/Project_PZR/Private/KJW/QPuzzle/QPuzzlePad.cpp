// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/QPuzzle/QPuzzlePad.h"
#include "KJW/QPuzzle/QPuzzleGameMode.h"
#include "KJW/QPuzzle/QPuzzleData.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UQPuzzlePad::NativeConstruct()
{
	Super::NativeConstruct();

	AButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedA);
	BButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedB);
	CButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedC);
	DButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedD);

	EnterButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedEnter);
	ClearButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedClear);

	ToLobbyButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedToLobby);

	TextBlocks.Add(ATextBlock);
	TextBlocks.Add(BTextBlock);
	TextBlocks.Add(CTextBlock);
	TextBlocks.Add(DTextBlock);

	Buttons.Add(AButton);
	Buttons.Add(BButton);
	Buttons.Add(CButton);
	Buttons.Add(DButton);

	ToLobbyButton->SetVisibility(ESlateVisibility::Collapsed);
	HideAllUI();
}

void UQPuzzlePad::HideAllUI()
{
	for (UButton* Button : Buttons)
		Button->SetVisibility(ESlateVisibility::Hidden);
	

}

void UQPuzzlePad::SetPuzzle()
{
	if (!QPGM) return;
	HideAllUI();
	UQPuzzleData* data = QPGM->GetPuzzleData();

	int32 num = data->ChoicesDescText.Num();
	for (int32 i = 0; i < num; ++i)
	{
		Buttons[i]->SetVisibility(ESlateVisibility::Visible);
		TextBlocks[i]->SetText(data->ChoicesDescText[i]);
	}

	bCheckAnwser = true;
}

void UQPuzzlePad::OnClickedA(){OnClickedButtonFunc(0);}
void UQPuzzlePad::OnClickedB() { OnClickedButtonFunc(1); }
void UQPuzzlePad::OnClickedC() { OnClickedButtonFunc(2); }
void UQPuzzlePad::OnClickedD() { OnClickedButtonFunc(3); }


void UQPuzzlePad::OnClickedButtonFunc(int32 index)
{
	if (!QPGM) return;
	QPGM->SelectAnswer(index);
}
void UQPuzzlePad::SetDisplay(EKGameState KGameState)
{
	
	if (KGameState == EKGameState::START)
	{
		SetPuzzle();
	}
	else if (KGameState == EKGameState::FINISH)
	{
		EnterButton->SetVisibility(ESlateVisibility::Collapsed);
		ClearButton->SetVisibility(ESlateVisibility::Collapsed);
		ToLobbyButton->SetVisibility(ESlateVisibility::Visible);
	}
	else if (KGameState == EKGameState::FAIL)
	{
		bCheckAnwser = false;
		//ReturnbCheckAnwserTimer
		EnterButton->SetVisibility(ESlateVisibility::Collapsed);
		GetWorld()->GetTimerManager().SetTimer(ReturnbCheckAnwserTimer,
			FTimerDelegate::CreateLambda([this]()
				{
					bCheckAnwser = true;
					EnterButton->SetVisibility(ESlateVisibility::Visible);
				}), 2.0f, false);
	}
}
void UQPuzzlePad::OnClickedClear()
{
	if (!QPGM) return;
	QPGM->ClearAnswer();
}

void UQPuzzlePad::OnClickedEnter()
{
	if (!QPGM) return;
	QPGM->CheckAnswer();
}

void UQPuzzlePad::OnClickedToLobby()
{
	FName LevelName = TEXT("TempLevel");
	UGameplayStatics::OpenLevel(this, LevelName);
}

