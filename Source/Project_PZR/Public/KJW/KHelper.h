// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

 class PROJECT_PZR_API KHelper
{
public:
	static FVector GetReflectionVector(const FVector& IncidentVector, const FVector& SurfaceNormal)
	{
		//�⺻ ����
		//R == V - 2 * N * (V dot N)
		// 
		//V : �Ի� ���� => ���̵����� ���� ����
		//N : �浹 ǥ���� ��� ���� (���� ����)

		FVector V = IncidentVector; // �Ի� ����
		FVector N = SurfaceNormal;	// ��� ����

		float DotProduct = FVector::DotProduct(V, N);  // 1. V�� N�� ���� ���

		FVector ProjectionOntoNormal = DotProduct * N; // 2. ��� ���� ���� ã��

		FVector ReflectionVector = V - 2 * ProjectionOntoNormal; // 3. �ݻ� ���� ���

		
		return ReflectionVector;
	}
};


