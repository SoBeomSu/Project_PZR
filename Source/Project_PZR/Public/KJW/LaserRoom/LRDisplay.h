// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJW/KHelper.h"
#include "LRDisplay.generated.h"

/**
 * 
 */



UCLASS()
class PROJECT_PZR_API ULRDisplay : public UUserWidget
{
	GENERATED_BODY()
	
	friend class ALRDisplayActor;

public:
	void SetDisplay(ELaserGameState LaserGameState);
private:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void ToBackFunc();

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UTextBlock* MainTextBlock;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* ToBackButton;

private:
	class ALaserRoomGameMode* LRGM;



};
