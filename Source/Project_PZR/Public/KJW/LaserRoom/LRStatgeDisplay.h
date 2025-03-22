// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LRStatgeDisplay.generated.h"

UCLASS()
class PROJECT_PZR_API ALRStatgeDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALRStatgeDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//현제 스테이지 상태를 띄우는
	void SetStageInfo();

private:
	UPROPERTY(VisibleAnywhere, Category = "StatgeDisplay")
	class USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, Category = "StatgeDisplay")
	class UTextRenderComponent* TextComp;

private:
	class ALaserRoomGameMode* LRGM;

};
