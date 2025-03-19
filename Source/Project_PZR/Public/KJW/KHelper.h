// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

 class PROJECT_PZR_API KHelper
{
public:
	static FVector GetReflectionVector(const FVector& IncidentVector, const FVector& SurfaceNormal)
	{
		FVector ReflectionVector = IncidentVector.MirrorByVector(SurfaceNormal);
		return ReflectionVector;
	}
};


