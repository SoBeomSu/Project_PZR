// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SBS_PlayerC.generated.h"


UCLASS()
class PROJECT_PZR_API ASBS_PlayerC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASBS_PlayerC();

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
	class UCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FSMcomp")
	class USBS_PlayerFSM* playerFSM;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_VR;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Turn;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_MouseRightButton;

	bool bRightclick = false;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_MouseLeftButton;

	bool bLeftclick = false;

	void Move(const struct FInputActionValue& Value);
	void Turn(const struct FInputActionValue& Value);
	void RMB_Start(const struct FInputActionValue& Value);
	void RMB_Complete(const struct FInputActionValue& Value);
	void LRB_Start(const struct FInputActionValue& Value);
	void LRB_Complete(const struct FInputActionValue& Value);

	FHitResult CameraLineTrace();

	AActor* GrabActor;
	void AttachActor(AActor* actor);
	void DetachActor(AActor* actor);
};
