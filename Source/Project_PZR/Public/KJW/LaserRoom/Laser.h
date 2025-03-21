// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class PROJECT_PZR_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//빔 이펙트를 그리는 함수
	void SetBeamEnd(FVector StartPoint, FVector EndPoint);
	//이펙트 지우는 함수
	void ResetBeam();

private:
	//레이저 이펙트
	UPROPERTY(EditAnywhere, Category = "Laser_Effects")
	class UNiagaraComponent* NiagaraComp;


};
