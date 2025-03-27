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

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* RightHandMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* LeftHandMesh;



	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_VR;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Move;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Turn;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_R_Grip_Click; // R 그립 우클릭
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_L_Grip_Click; // L 그립 좌클릭
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Button_A; // A버튼
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Button_X; // X버튼
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Thumb_R; // 오른쪽 엄지스틱
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Thumb_L; // 오른쪽 엄지스틱

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
	void ButtonPressed_A();
	void ButtonPressed_X();

	void ButtonPressed(EVRButton VRButton);
	void ButtonReleased();

	void Move(const struct FInputActionValue& Value);
	void Thumb_RInput(const struct FInputActionValue& Value);
	void Turn(const struct FInputActionValue& Value);

	FHitResult CameraLineTraceHitResult();

	void AttachActor(AActor* actor);
	void DetachActor(AActor* actor);
};
