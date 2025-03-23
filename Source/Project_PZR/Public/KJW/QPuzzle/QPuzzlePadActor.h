// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KJW/KHelper.h"
#include "KJW/KVRObjectInterface.h"
#include "QPuzzlePadActor.generated.h"

UCLASS()
class PROJECT_PZR_API AQPuzzlePadActor : public AActor ,public IKVRObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQPuzzlePadActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	bool virtual IsGrab() override { return true; } ;
	void virtual StartGrab(AActor* HandActor) override;
	void virtual StopGrab(AActor* HandActor) override;
	void virtual RotObject(const FRotator AddRotator) override;

private:
	void SetDisplay(EKGameState LaserGameState);
	void UpdateAnswerDisplay(EKGameState LaserGameState);
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
