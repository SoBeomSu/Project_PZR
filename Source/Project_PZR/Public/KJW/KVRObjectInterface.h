// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KVRObjectInterface.generated.h"

UENUM()
enum class EVRButton
{
	NONE,
	
	Right_A_Button,
	Right_B_Button,
	Left_X_Button,
	Left_Y_Button,



	Hand_ThumbUp_Right,
	Hand_ThumbUp_Left,
	Hand_Point_Right,
	Hand_Point_Left,
	Hand_Trigger_Right,
	Hand_Trigger_Left,

};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKVRObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_PZR_API IKVRObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool  IsGrab() { return false; };
	
	virtual void  StartGrab(AActor* HandActor) {};
	virtual void  StopGrab(AActor* HandActor) {};
	virtual void  RotObject(const FRotator AddRotator) {};

	//손으로 오브젝트 잡기 시작
	virtual void StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight) {};
	//손으로 오브젝트 잡기 종료
	virtual void StopGrab(class UMotionControllerComponent* MontionComp, bool IsRight) {};
	//오브젝트 들고 있을때
	virtual void  Grabbing(class UMotionControllerComponent* MontionComp, bool IsRight) {};
	//컨트롤러를 통해 오브젝트 회전
	virtual void  RotObject(class UMotionControllerComponent* MontionComp , bool IsRight , const FRotator AddRotator) {};
	//VR버튼이 눌렀을 때 호출
	//virtual void  OnButtonPressed(class USceneComponent* HitComponent, EVRButton VRButton) {};
	virtual void  OnButtonPressed(FHitResult& HitResult, EVRButton VRButton) {};
	//VR버튼이 떼어졌을 때 호출
	virtual void  OnButtonReleased(FHitResult& HitResult, EVRButton VRButton) {};

	//Thumbstick 입력을 받아오는
	virtual void OnThumbstickValue(class UMotionControllerComponent* MontionComp, bool IsRight, const FVector2D& Value) {};

};
