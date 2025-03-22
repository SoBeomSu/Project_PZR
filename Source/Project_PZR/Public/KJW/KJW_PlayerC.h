// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KJW_PlayerC.generated.h"

UCLASS()
class PROJECT_PZR_API AKJW_PlayerC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKJW_PlayerC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Move(const struct FInputActionValue& Value);
	void Turn(const struct FInputActionValue& Value);

	void InteractWidget();
	void InteractWidgetHover();
protected:
	UPROPERTY(VisibleAnywhere, Category = "VR")
	class UCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, Category = "VR")
	class UWidgetInteractionComponent* IneractionComp;

public:
	UPROPERTY(EditDefaultsOnly, Category = "VR_input")
	class UInputMappingContext* IMC_VR;

	UPROPERTY(EditDefaultsOnly, Category = "VR_input")
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "VR_input")
	class UInputAction* IA_Mouse;

	UPROPERTY(EditDefaultsOnly, Category = "VR_input")
	class UInputAction* IA_VRMouse_L;
	
	UPROPERTY(EditDefaultsOnly, Category = "VR_input")
	class UInputAction* IA_VRMouse_R;
	
	UPROPERTY(EditDefaultsOnly, Category = "VR_input")
	class UInputAction* IA_KeyE;

	UPROPERTY(EditDefaultsOnly, Category = "VR_input")
	class UInputAction* IA_KeyQ;

	UPROPERTY(EditDefaultsOnly, Category = "VR_input")
	class UInputAction* IA_InteractWidget;


//거울 오브젝트를 잡기 위한
public :
	//잡은 물체 저장
	class IKVRObjectInterface* GrabObj;
	//잡기 행동
	void GrabStart();
	void GrabEnd();
	//잡은 물체를 회전 시키기 위한
	void LRotGrabObj();
	void RRotGrabObj();
};
