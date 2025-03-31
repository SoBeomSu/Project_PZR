// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SBS_AnimalAnim.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_PZR_API USBS_AnimalAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGrab = false;

};
