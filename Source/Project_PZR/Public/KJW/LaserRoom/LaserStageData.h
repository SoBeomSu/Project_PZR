// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LaserStageData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FLaserRoomActorData
{
    GENERATED_BODY()

public:
    // 스폰할 액터 클래스 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ActorClass;

    // 액터들이 스폰될 위치 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnLocation;

    // 액터 회전값
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator SpawnRotation;

    // 액터의 스케일 값 
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnScale = FVector::OneVector;
};

UCLASS(BlueprintType)
class PROJECT_PZR_API ULaserStageData : public UDataAsset
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserRoom")
	int32 Stage = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserRoom")
    int32 NeedLaser = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LaserRoom")
    TArray<FLaserRoomActorData> LaserRoomActorDatas;
		
};
