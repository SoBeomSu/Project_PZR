// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LaserRoomGameMode.h"
#include "KJW/LaserRoom/LaserStageData.h"
#include "KJW/LaserRoom/Laser.h"
#include "KJW/LaserRoom/LRStatgeDisplay.h"


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
			SetDisplay();
			SpawnStageActor();
			LaserGameState = ELaserGameState::INGAME;
		}
		break;
	}
	case ELaserGameState::FINISH:
	{
		SetDisplay();
		break;
	}
	default:
		break;
	}

	UpdateStageDelegate.Broadcast(LaserGameState);
}

void ALaserRoomGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 10; ++i)
	{
		SpawnLaser();
	}
	

	GetWorld()->GetTimerManager().SetTimer(LaserGameStateTimerHandle,
		FTimerDelegate::CreateLambda([this]()
			{
				ChangeLaserGameState(ELaserGameState::START);
			}), 2.0f, false);
	
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

void ALaserRoomGameMode::SpawnLaser()
{
	ensure(LaserClass);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	ALaser* NewLaser = GetWorld()->SpawnActor<ALaser>(LaserClass , FVector(-100.0f) , FRotator(0.0f), SpawnParams);
	NewLaser->ResetBeam();

	LaserPool.Enqueue(NewLaser);
}

ALaser* ALaserRoomGameMode::GetLaser()
{
	ALaser* Laser = nullptr;
	if (LaserPool.IsEmpty())
	{
		SpawnLaser();
	}

	
	LaserPool.Dequeue(Laser);
	Laser->SetActorHiddenInGame(false);
	
	return Laser;
}

void ALaserRoomGameMode::ReturnLaser(ALaser* Laser)
{
	Laser->ResetBeam();
	Laser->SetActorHiddenInGame(true);
	LaserPool.Enqueue(Laser);
}

void ALaserRoomGameMode::SetDisplay()
{
	if (!Display) return;

	Display->SetStageInfo();
}
