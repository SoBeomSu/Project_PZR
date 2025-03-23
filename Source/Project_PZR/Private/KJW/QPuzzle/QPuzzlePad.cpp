// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/QPuzzle/QPuzzlePad.h"
#include "KJW/QPuzzle/QPuzzleGameMode.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UQPuzzlePad::NativeConstruct()
{
	Super::NativeConstruct();

	AButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedA);
	BButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedB);
	CButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedC);
	DButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedD);

	EnterButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedEnter);
	ClearButton->OnClicked.AddDynamic(this, &ThisClass::OnClickedClear);
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

