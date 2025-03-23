// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBS_MathPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PZR_API USBS_MathPuzzle : public UUserWidget
{
	GENERATED_BODY()
public:

	float PageN1;
	float pageN2;
	float pageN3;
	float PuzzleAnswer;
};
