// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KJW/KHelper.h"
#include "QPDisplayActor.generated.h"

UCLASS()
class PROJECT_PZR_API AQPDisplayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQPDisplayActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetAnswerText(FText text);
private:
	void SetDisplay(EKGameState LaserGameState);
	void SetAnswer(EKGameState LaserGameState);
private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* WidgetComp;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UQPDisplay* QPDisplay;

	class AQPuzzleGameMode* QPGM = nullptr;


};
