// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "KJW/KVRObjectInterface.h"

#include "SBS_Animal.generated.h"

UCLASS()
class PROJECT_PZR_API ASBS_Animal : public APawn, public IKVRObjectInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASBS_Animal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FSM")
	class USBS_AnimalFSM* AnimalFSM;

	int Health = 100;

	virtual bool  IsGrab() override { return true; };
	virtual void StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
	//손으로 오브젝트 잡기 종료
	virtual void StopGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
	//오브젝트 들고 있을때
	virtual void  Grabbing(class UMotionControllerComponent* MontionComp, bool IsRight) override;
};
