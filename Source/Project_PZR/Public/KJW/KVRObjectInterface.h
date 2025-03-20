// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KVRObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKVRObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_PZR_API IKVRObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	
	bool virtual IsGrab() { return false; };
	void virtual StartGrab(AActor* HandActor) {};
	void virtual StopGrab(AActor* HandActor) {};
	void virtual RotObject(const FRotator AddRotator) {};

};
