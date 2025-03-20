// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndLaserPoint.generated.h"

UCLASS()
class PROJECT_PZR_API AEndLaserPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndLaserPoint();

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
	class UStaticMeshComponent* MeshComp;

public:
	// 성공 시 적용할 머티리얼
	UPROPERTY(EditAnywhere, Category = "Laser")
	UMaterialInterface* SuccessMaterial;  
	// 실패 시 적용할 머티리얼
	UPROPERTY(EditAnywhere, Category = "Laser")
	UMaterialInterface* FailMaterial;     

	bool bSucceed = false;
	//정보 갱신
	void SetGoalInfo();
	//성공에 따른 머티리얼 셋팅
	void SetGoalMt();
	//목표 갯수
	UPROPERTY(EditAnywhere, Category = "End_Point")
	int32 GoalCount = 1;

	void AddMirrorPoint(class ALaserMirror* LaserMirror);
	void RemoveMirrorPoint(class ALaserMirror* LaserMirror);
	//현제 레이저가 들어오는 거울들
	TArray<class ALaserMirror*> Mirrors;

public:
	//UI
	UPROPERTY(EditAnywhere, Category = "UI")
	class UWidgetComponent* TextWidget;

	UPROPERTY()
	class UTextboard* Textboard;

	void SetGoalText();

};
