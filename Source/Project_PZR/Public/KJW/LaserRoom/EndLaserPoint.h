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
	// ���� �� ������ ��Ƽ����
	UPROPERTY(EditAnywhere, Category = "Laser")
	UMaterialInterface* SuccessMaterial;  
	// ���� �� ������ ��Ƽ����
	UPROPERTY(EditAnywhere, Category = "Laser")
	UMaterialInterface* FailMaterial;     

	bool bSucceed = false;
	//���� ����
	void SetGoalInfo();
	//������ ���� ��Ƽ���� ����
	void SetGoalMt();
	//��ǥ ����
	UPROPERTY(EditAnywhere, Category = "End_Point")
	int32 GoalCount = 1;

	void AddMirrorPoint(class ALaserMirror* LaserMirror);
	void RemoveMirrorPoint(class ALaserMirror* LaserMirror);
	//���� �������� ������ �ſ��
	TArray<class ALaserMirror*> Mirrors;

public:
	//UI
	UPROPERTY(EditAnywhere, Category = "UI")
	class UWidgetComponent* TextWidget;

	UPROPERTY()
	class UTextboard* Textboard;

	void SetGoalText();

};
