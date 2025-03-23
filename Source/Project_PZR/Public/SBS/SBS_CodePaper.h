// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "SBS_CodePaper.generated.h"

UCLASS()
class PROJECT_PZR_API ASBS_CodePaper : public AActor
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
    USceneComponent* Root;

    UPROPERTY(EditAnywhere, Category = "Text")
    UTextRenderComponent* TextDisplay;

    // 표시할 변수
    UPROPERTY(EditAnywhere, Category = "Text")
    int32 DisplayValue = 42;

	void UpdateTextDisplay();
};
