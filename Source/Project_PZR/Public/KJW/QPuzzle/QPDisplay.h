// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJW/KHelper.h"
#include "QPDisplay.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PZR_API UQPDisplay : public UUserWidget
{
	GENERATED_BODY()
	
	friend class AQPDisplayActor;

private:
	virtual void NativeConstruct() override;

public: 
	void SetDisplay(EKGameState LaserGameState);
	void SetAnswerText(FText text);
private:
	void HideAllDisplay();
	void SetQPuzzle();
	void SetScore();

private:
	class AQPuzzleGameMode* QPGM;

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* MainDescTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* SubDescTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* ATextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* BTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* CTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* DTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* StateInfoTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* AnswerTextBlock;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* MyAnwserTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UHorizontalBox* ScoreBox;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* CurScoreTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* GoalScoreTextBlock;

	TArray<class UTextBlock*> ChoiceTexts;

	
};
