// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/QPuzzle/QPuzzleGameMode.h"
#include "KJW/QPuzzle/QPuzzleData.h"


AQPuzzleGameMode::AQPuzzleGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AQPuzzleGameMode::BeginPlay()
{
	
	InitPuzzleDatas();

	//2초후 게임시작 하겠끔
	GetWorld()->GetTimerManager().SetTimer(QPuzzleGameStateTimerHandle,
		FTimerDelegate::CreateLambda([this]()
			{
				ChangeLaserGameState(EKGameState::START);
			}), 2.0f, false);
}

void AQPuzzleGameMode::ChangeLaserGameState(EKGameState NewLaserGameState)
{
	if (QPuzzleGameState == NewLaserGameState) { return; }

	QPuzzleGameState = NewLaserGameState;

	switch (QPuzzleGameState)
	{
	case EKGameState::NONE:
		break;
	case EKGameState::START:
	{
		bool ChangeSuccess = ChangeQPuzzle();
		if (!ChangeSuccess)
		{
			ChangeLaserGameState(EKGameState::FINISH);
			return;
		}

		break;
	}
	case EKGameState::INGAME:
		break;
	case EKGameState::CLEAR:
	{
		PuzzleCount++;
		ClearAnswer();
		if (GoalCount == PuzzleCount)
		{
			ChangeLaserGameState(EKGameState::FINISH);
			return;
		}
		else
		{
			ChangeLaserGameState(EKGameState::START);
			return;
		}

		break;
	}
	case EKGameState::FINISH:
	{

		break;
	}
	default:
		break;
	}

	UpdateStageDelegate.Broadcast(QPuzzleGameState);

}

bool AQPuzzleGameMode::ChangeQPuzzle()
{
	if (QPuzzleDatas.IsEmpty())return false;
	if (QPuzzleIndex.IsEmpty()) return false;
	if (GoalCount == PuzzleCount) return false;

	int32 Rand = FMath::RandRange(0, QPuzzleIndex.Num() -1);
	int32 QIndex = QPuzzleIndex[Rand];

	QPuzzleIndex.RemoveAt(Rand);
	UE_LOG(LogTemp, Warning, TEXT("%d"), QIndex);
	CurQPuzzleData = QPuzzleDatas[QIndex];


	return true;
}

void AQPuzzleGameMode::SelectAnswer(int32 Index)
{
	if (!CurQPuzzleData) return;

	CurAnswer = CurQPuzzleData->ChoicesDescText[Index];

	UpdateAnswerDelegate.Broadcast(QPuzzleGameState);
}


void AQPuzzleGameMode::CheckAnswer()
{
	if (CurAnswer.EqualTo(CurQPuzzleData->Ansertext))
	{
		ChangeLaserGameState(EKGameState::CLEAR);
	}
	else
	{
		UpdateAnswerDelegate.Broadcast(EKGameState::FAIL);
		return;
	}

	UpdateAnswerDelegate.Broadcast(QPuzzleGameState);
}

void AQPuzzleGameMode::ClearAnswer()
{
	CurAnswer = FText::FromString("");
	UpdateAnswerDelegate.Broadcast(QPuzzleGameState);
}

void AQPuzzleGameMode::InitPuzzleDatas()
{
	if (QPuzzleDatas.IsEmpty()) return;

	for (int i = 0; i < QPuzzleDatas.Num(); ++i)
	{
		QPuzzleIndex.Add(i);
	}


}
