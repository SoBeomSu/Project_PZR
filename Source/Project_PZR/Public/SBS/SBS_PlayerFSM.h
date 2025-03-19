// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBS_PlayerFSM.generated.h"

UENUM()
enum class ESBSPlayerState
{
	Idle UMETA(DisplayName = "대기"),
	Move UMETA(DisplayName = "이동"),
	Grab UMETA(DisplayName = "그랩")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PZR_API USBS_PlayerFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USBS_PlayerFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FSM")
	ESBSPlayerState mState = ESBSPlayerState::Idle;

	void IdleState();
	void MoveState();
	void GrabState();
};
