// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KJW/KVRObjectInterface.h"
#include "LaserMirror.generated.h"

UCLASS()
class PROJECT_PZR_API ALaserMirror : public AActor , public IKVRObjectInterface
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
	//다음 레이저 이여 발사하기
	void NextLaserStart(const struct FHitResult& HitInfo, const FVector& InDir, const float& LaserLength, TArray<FVector>& Lines , bool& IsGoal);

public:
	//플레이어와의 상호작용을 위한 함수
	virtual bool IsGrab() override { return true; };
	virtual void StartGrab(AActor* HandActor) override;
	virtual void StopGrab(AActor* HandActor) override;
	virtual void RotObject(const FRotator AddRotator) override;

	//손으로 오브젝트 잡기 시작
	virtual void StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
	//손으로 오브젝트 잡기 종료
	virtual void StopGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
	
public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MirrorComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BottomComp;


public:
	UPROPERTY(EditAnywhere, Category = "MirrorLaser")
	bool bDrawLaser = false;


private:
	UPROPERTY()
	TWeakObjectPtr<class AEndLaserPoint> EndLaserPoint;



};
