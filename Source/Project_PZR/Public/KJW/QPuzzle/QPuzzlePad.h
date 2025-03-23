// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJW/KHelper.h"
#include "QPuzzlePad.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PZR_API UQPuzzlePad : public UUserWidget
{
	GENERATED_BODY()

public:
	friend class AQPuzzlePadActor;

private:
	virtual void NativeConstruct() override;
public:
	void HideAllUI();
	void SetPuzzle();

private:
	UFUNCTION()
	void OnClickedA();
	UFUNCTION()
	void OnClickedB();
	UFUNCTION()
	void OnClickedC();
	UFUNCTION()
	void OnClickedD();

	UFUNCTION()
	void OnClickedClear();
	UFUNCTION()
	void OnClickedEnter();

	UFUNCTION()
	void OnClickedToLobby();

	void OnClickedButtonFunc(int32 index);

	void SetDisplay(EKGameState KGameState);

	

private:
	class AQPuzzleGameMode* QPGM;
	
	bool bCheckAnwser = false;

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* AButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* CButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* DButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* ClearButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* EnterButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* ToLobbyButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* ATextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* BTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* CTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* DTextBlock;

private:
	TArray<class UTextBlock*> TextBlocks;
	TArray<class UButton*> Buttons;


	FTimerHandle ReturnbCheckAnwserTimer;
};
