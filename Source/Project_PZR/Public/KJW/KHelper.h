// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

 class PROJECT_PZR_API KHelper
{
public:
	static FVector GetReflectionVector(const FVector& IncidentVector, const FVector& SurfaceNormal)
	{
		//기본 공식
		//R == V - 2 * N * (V dot N)
		// 
		//V : 입사 벡터 => 빛이들어오는 방향 벡터
		//N : 충돌 표면의 노멀 벡터 (단위 벡터)

		FVector V = IncidentVector; // 입사 벡터
		FVector N = SurfaceNormal;	// 노멀 벡터

		float DotProduct = FVector::DotProduct(V, N);  // 1. V와 N의 내적 계산

		FVector ProjectionOntoNormal = DotProduct * N; // 2. 노멀 방향 성분 찾기

		FVector ReflectionVector = V - 2 * ProjectionOntoNormal; // 3. 반사 벡터 계산

		
		return ReflectionVector;
	}
};


