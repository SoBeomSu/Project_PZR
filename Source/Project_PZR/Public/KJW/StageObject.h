// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StageObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStageObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_PZR_API IStageObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void  Start() { IsStart = true; };
	virtual void  End() { IsStart = false; };
protected:

	bool IsStart = false;


};
