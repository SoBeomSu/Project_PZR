// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LaserRoomGameMode.h"
#include "KJW/LaserRoom/LaserStageData.h"

ALaserRoomGameMode::ALaserRoomGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALaserRoomGameMode::ChangeLaserGameState(ELaserGameState NewLaserGameState)
{
	if (LaserGameState == NewLaserGameState) { return; }
	
	LaserGameState = NewLaserGameState;

	switch (LaserGameState)
	{
	case ELaserGameState::NONE:
		break;
	case ELaserGameState::START:
	{
		SpawnStageActor();
		break;
	}
	case ELaserGameState::INGAME:
		break;
	case ELaserGameState::CLEAR:
	{
		if (Stage == MaxStage)
		{
			ChangeLaserGameState(ELaserGameState::FINISH);
			return;
		}
		else
		{
			ResetStageActor();
			Stage++;
			SpawnStageActor();
		}
		break;
	}
	case ELaserGameState::FINISH:
		break;
	default:
		break;
	}
}

void ALaserRoomGameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeLaserGameState(ELaserGameState::START);
}

void ALaserRoomGameMode::SpawnStageActor()
{
	if (StageDatas.IsEmpty()) return;

	int32 index = Stage - 1;
	if (StageDatas.Num() <= index) return;

	ULaserStageData* StageData = StageDatas[index];

	// 스폰 파라미터 설정
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	NeedLaser = StageData->NeedLaser;

	SpawnedActors.Empty();
	for (auto& data : StageData->LaserRoomActorDatas)
	{
		if (!data.ActorClass) return;

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
			data.ActorClass,
			data.SpawnLocation,
			data.SpawnRotation,
			SpawnParams
		);

		if (SpawnedActor)
		{
			SpawnedActor->SetActorScale3D(data.SpawnScale);
		}

		SpawnedActors.Add(SpawnedActor);
	}
	

}

void ALaserRoomGameMode::ResetStageActor()
{
	for (int i = 0; i < SpawnedActors.Num(); i++)
	{
		SpawnedActors[i]->Destroy();
	}
	
	SpawnedActors.Empty();
}
