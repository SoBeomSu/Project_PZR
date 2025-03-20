// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserMirror.generated.h"

UCLASS()
class PROJECT_PZR_API ALaserMirror : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserMirror();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MirrorComp;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* MirrorArrowComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BottomComp;


public:
	UPROPERTY(EditAnywhere, Category = "MirrorLaser")
	bool bStartLaser = false;

public:
	//다음 레이저 이여 발사하기
	void NextLaserStart(const struct FHitResult& HitInfo , const FVector& InDir , const float& LaserLength);

private:
	UPROPERTY()
	TWeakObjectPtr<class AEndLaserPoint> EndLaserPoint;
};
