// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EKGameState : uint8
{
	NONE UMETA(DisplayName = "None"),
	START UMETA(DisplayName = "Start"),
	INGAME UMETA(DisplayName = "InGame"),
	FAIL UMETA(DisplayName = "Fail"),
	CLEAR UMETA(DisplayName = "Clear"),
	FINISH UMETA(DisplayName = "Finish"),
};

UENUM(BlueprintType)
enum class EEasing : uint8
{
	Linear ,
	EaseOutQuint, //느리게 시작 → 점점 가속
	EaseInQuint, //빠르게 시작 → 점점 감속
	
};


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

		//(V dot N)
		float DotProduct = FVector::DotProduct(V, N);  // 1. V와 N의 내적 계산
		//N * (V dot N)
		FVector ProjectionOntoNormal = DotProduct * N; // 2. 노멀 방향 성분 찾기
		// V - 2 * N * (V dot N)
		FVector ReflectionVector = V - 2 * ProjectionOntoNormal; // 3. 반사 벡터 계산

		return ReflectionVector;
	}

	template <typename T>
	static T Lerp(const T& A, const T& B, float Alpha , EEasing Easing = EEasing::Linear)
	{
		//기본 Lerp 공식 
		// linear 
		//Lerp = A + (B - A ) * Alpha
		//FMath::Lerp(LDoor_ClosePos, LDoor_OpenPos, percent);
		float x = Alpha;// 0 ~ 1
		switch (Easing)
		{
		case EEasing::Linear: {	break;}
		//느리게 시작 → 점점 가속
		case EEasing::EaseOutQuint:{x = 1 - FMath::Pow(1 - x, 5);break;}
		//빠르게 시작 → 점점 감속
		case EEasing::EaseInQuint:{ x =  x * x * x * x * x; break; }
		default:
			break;
		}
		
		return A + (B - A) * x;
	}
	

};


