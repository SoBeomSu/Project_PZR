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
	void AddMirrorPoint(class ALaserMirror* LaserMirror);
	void RemoveMirrorPoint(class ALaserMirror* LaserMirror);
private:
	//정보 갱신
	void SetGoalInfo();
	//성공에 따른 머티리얼 셋팅
	void SetGoalMt(const float& DeltaTime);
	//골 텍스트 갱신
	void SetGoalText();
public:

	//현제 레이저가 들어오는 거울들
	TArray<class ALaserMirror*> Mirrors;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;
public:
	UPROPERTY(EditAnywhere, Category = "End_Point")
	int32 GoalCount = 1;
	UPROPERTY(EditAnywhere, Category = "Laser")
	FColor BaseColor = FColor::Black;
	UPROPERTY(EditAnywhere, Category = "Laser")
	float EmissiveScale = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Laser")
	float MaxEmissiveScale = 10.0f;
	UPROPERTY(EditAnywhere, Category = "Laser")
	float NeedTime = 3.0f;
	UPROPERTY(EditAnywhere, Category = "Laser")
	float CurNeedTime = 0.0f;

private:

	class ALaserRoomGameMode* LaserGamemode;

public:
	//UI
	UPROPERTY(EditAnywhere, Category = "UI")
	class UWidgetComponent* TextWidget;

	UPROPERTY()
	class UTextboard* Textboard;

	

};
