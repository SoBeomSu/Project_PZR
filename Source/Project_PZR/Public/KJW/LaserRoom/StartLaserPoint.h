// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartLaserPoint.generated.h"

UCLASS()
class PROJECT_PZR_API AStartLaserPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStartLaserPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	void StartSetLaser();
	void DrawLaser();
	void GetLaser(int32 Count);
	void ReturnLaser();

	void CheckIsGoalLaser();
private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LaserComp;
	
	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* LaserArrowComp;

private:
	UPROPERTY(EditAnywhere, Category = "StartLaser" , meta = (AllowPrivateAccess = true))
	bool bDrawLaser = false;

	UPROPERTY(EditAnywhere , Category = "StartLaser", meta = (AllowPrivateAccess = true))
	float LaserLength = 3000.0f;
	
	UPROPERTY(EditAnywhere, Category = "StartLaser", meta = (AllowPrivateAccess = true))
	float LaserDelay = 0.15f;

	UPROPERTY(VisibleAnywhere, Category = "StartLaser", meta = (AllowPrivateAccess = true))
	float LaserDelayTimer = 0.00f;
	
	UPROPERTY(VisibleAnywhere, Category = "StartLaser", meta = (AllowPrivateAccess = true))
	bool IsGoal = false;

private:
	class ALaserRoomGameMode* LRGM;

private:
	//레이저 이펙트
	UPROPERTY(EditAnywhere, Category = "Laser_Effects")
	class UNiagaraComponent* NiagaraComp;
	//사용하고 있는 레이저
	TArray<class ALaser*> Lasers;
	//레이저 좌표 저장
	TArray<FVector> Lines;

	class AEndLaserPoint* CurentEndLaserPoint = nullptr;
};
