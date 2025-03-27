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
	void NextLaserStart(const struct FHitResult& HitInfo, const FVector& InDir, const float& LaserLength, TArray<FVector>& Lines , bool& IsGoal ,bool& IsReal);

public:

	virtual bool  IsGrab();// { return !IsGrabbing; };

	//손으로 오브젝트 잡기 시작
	virtual void StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
	//손으로 오브젝트 잡기 종료
	virtual void StopGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
	//버튼 반응
	virtual void  OnButtonPressed(FHitResult& HitResult, EVRButton VRButton) override;
	//썸스틱 입력
	virtual void OnThumbstickValue(class UMotionControllerComponent* MontionComp, bool IsRight, const FVector2D& Value) override;

public:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MirrorMeshComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* TempMirrorMeshComp;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* MirroBoxComp;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* TempMirroBoxComp;

public:
	UPROPERTY(EditAnywhere, Category = "MirrorLaser")
	bool bDrawLaser = false;


private:
	UPROPERTY()
	TWeakObjectPtr<class AEndLaserPoint> EndLaserPoint;

	
	
public:
	//거울을 집을때 기존 크기에서 0.1 사이즈 정도로 줄여지면서 손안으로 오겠끔

	bool IsGrabbing = false;
	bool IsComplete = false;
	class UMotionControllerComponent* HandComp;
	FTimerHandle MoveToHandTimerHandle;
	FTimerHandle MoveToPlaceTimerHandle;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float MiniScale = 0.1;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	float OrginScale = 1.0f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float MoveToHandTime = 0.5f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	bool bEaseOutQuint = false;

	FVector OrginPos;
	FVector MovePos;
	float MoveToHandDeltatime = 0.02f;
	float MoveToHandTimer = 0.0f;


	void UpdateScale();
	void MoveToHand();
	void MoveToPlace();
	void DrawTempMirror();
	void TempMirrorRot(FRotator AddRot);
};
