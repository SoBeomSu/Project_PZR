// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "KJW/KVRObjectInterface.h"
#include "SBS_Bomb.generated.h"

UCLASS()
class PROJECT_PZR_API ASBS_Bomb : public AActor, public IKVRObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASBS_Bomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere)
    class USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Boxcollision;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    TArray<UBoxComponent*> NumberCollisions; // 0~9 콜리전

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* EnterKey;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* DeleteKey;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* PasswordWidget;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* TimeLeftWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCorrect = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Password;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Answer = "3958";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInterface* OneGreen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInterface* TwoGreen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInterface* ThreeGreen;

	class ASBS_GameMode* GameMode;
	FString WritePassword(int Numbers);

	class ASBS_Animal* Animal;

	void SetupKeypad();	
	void PressEnter();
	void PressDelete();

	void UpdateWidgetText();
	void UpdateBombMaterial(int CorrectCount);

	virtual void  OnButtonPressed(FHitResult& HitResult, EVRButton VRButton) override;
	virtual bool IsGrab() override { return true; };
	virtual void StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
	//손으로 오브젝트 잡기 종료
	virtual void StopGrab(class UMotionControllerComponent* MontionComp, bool IsRight) override;
};
