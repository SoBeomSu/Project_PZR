// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Textboard.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PZR_API UTextboard : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Textboard;

public:
	UFUNCTION(BlueprintCallable)
	void SetTextBlock(FText text);

};
