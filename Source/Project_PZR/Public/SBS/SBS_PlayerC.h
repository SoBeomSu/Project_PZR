// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SBS_GameStartButton.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_MouseLeftButton;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_PressA;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_PressX;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* VRCamera;
	//모션컨트롤러 등록
	UPROPERTY(VisibleAnyWhere, Category = "MotionController")
	class UMotionControllerComponent* LeftHand;
	UPROPERTY(VisibleAnyWhere, Category = "MotionController")
	class UMotionControllerComponent* RightHand;
	UPROPERTY(VisibleAnyWhere, Category = "MotionController")
	class UMotionControllerComponent* RightAim;




	class ASBS_GameMode* GameMode;
	class ASBS_LightSwitch* LightSwitch;
	ASBS_GameStartButton* StartButton;
	
	bool bRightclick = false;
	bool bLeftclick = false;

	AActor* GrabActor;
	float MoveSpeedVal = 1;

	class IKVRObjectInterface* GrabObj;
	void GrabStart_R();
	void GrabEnd_R();
	void GrabStart_L();
	void GrabEnd_L();
	void PressA();
	void PressX();

	void Move(const struct FInputActionValue& Value);
	void Turn(const struct FInputActionValue& Value);

	FHitResult CameraLineTrace();

	void AttachActor(AActor* actor);
	void DetachActor(AActor* actor);
};
