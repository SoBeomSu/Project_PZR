// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KJW/KHelper.h"
#include "LRDisplayActor.generated.h"

UCLASS()
class PROJECT_PZR_API ALRDisplayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALRDisplayActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* WidgetComp;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class ULRDisplay* LRDisplay;

private:
	void SetDisplay(ELaserGameState LaserGameState);

};
