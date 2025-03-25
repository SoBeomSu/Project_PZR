// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KJW/KVRObjectInterface.h"
#include "SBS_AnimalFSM.generated.h"

UENUM()
enum class ESBS_AnimalState
{
	Stay UMETA(DisplayName = "시작전"),
	Idle UMETA(DisplayName = "대기"),
	Move UMETA(DisplayName = "이동"),
	InAir UMETA(DisplayName = "잡힘"),
	Burning UMETA(DisplayName = "타는중"),
	Dead UMETA(DisplayName = "죽음")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PZR_API USBS_AnimalFSM : public UActorComponent, public IKVRObjectInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USBS_AnimalFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	class ASBS_Animal* Animal;
	class ASBS_FirePit* Firepit;
	class ASBS_GameMode* GameMode;

	void SetState(ESBS_AnimalState Newstate)
	{
		mState = Newstate;
		UE_LOG(LogTemp, Log, TEXT("FSM State changed to: %s"), *UEnum::GetValueAsString(mState));
	}
	void Stay(float Deltatime);
	void IdleState();
	void MoveState();
	void InAir();
	void Burning();
	void Dead();

	float CurrentTime = 0;
	float StayTime = 5;
	float BurnTime = 1;

	FVector AnimalDir;
	float AnimalSpeed = 200;
	float DirChangeRate = 3;
	int AnimalHealth;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FSM")
	ESBS_AnimalState mState = ESBS_AnimalState::Stay;





};
