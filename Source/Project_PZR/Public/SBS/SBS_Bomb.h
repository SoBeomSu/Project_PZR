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


	UPROPERTY(VisibleAnywhere, Category = "Components")
    class USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    TArray<UBoxComponent*> NumberCollisions; // 1~9 ÄÝ¸®Àü

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* StaticMesh;

	void SetupKeypad();
	virtual void  OnButtonPressed(FHitResult& HitResult, EVRButton VRButton) override;
	FString EnterPassword(int Numbers);
};
