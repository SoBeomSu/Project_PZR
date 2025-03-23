// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QPuzzlePadActor.generated.h"

UCLASS()
class PROJECT_PZR_API AQPuzzlePadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQPuzzlePadActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* WidgetComp;


	class UQPuzzlePad* QPPad;
	class AQPuzzleGameMode* QPGM = nullptr;
};
