// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "KJW/KVRObjectInterface.h"
#include "SBS_CodePaper.generated.h"

UCLASS()
class PROJECT_PZR_API ASBS_CodePaper : public AActor, public IKVRObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBS_CodePaper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
    class USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Collision")
	class UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere, Category = "StaticMesh")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Widget")
	class UWidgetComponent* WidgetComp;


    // 표시할 변수
    UPROPERTY(EditAnywhere, Category = "Text")
    int32 DisplayValue = 42;

	virtual void StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
	//손으로 오브젝트 잡기 종료
	virtual void StopGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;

	void UpdateTextDisplay();
};
