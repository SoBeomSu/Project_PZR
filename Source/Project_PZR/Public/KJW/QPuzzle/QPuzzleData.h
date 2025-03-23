// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QPuzzleData.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum  class EQPuzzleType : uint8
{
	NONE UMETA(DisplayName = "None"),
	INT UMETA(DisplayName = "INT"),
	TEXT UMETA(DisplayName = "TEXT"),

};

UCLASS()
class PROJECT_PZR_API UQPuzzleData : public UDataAsset
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPuzzleData")
	int32 PuzzleNo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPuzzleData")
	EQPuzzleType QPuzzleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPuzzleData")
	FText MainDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPuzzleData")
	FText SubDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPuzzleData")
	int32 ChoiceNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPuzzleData")
	TArray<FText> ChoicesText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPuzzleData")
	TArray<FText> ChoicesDescText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPuzzleData")
	int32 AnserInt = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QPuzzleData")
	FText Ansertext;
};

