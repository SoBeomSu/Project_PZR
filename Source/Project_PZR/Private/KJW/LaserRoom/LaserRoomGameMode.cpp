// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LaserRoomGameMode.h"
#include "KJW/LaserRoom/LaserStageData.h"
#include "KJW/LaserRoom/Laser.h"
#include "KJW/LaserRoom/LRStatgeDisplay.h"
#include "KJW/LaserRoom/LRoom.h"



ALaserRoomGameMode::ALaserRoomGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALaserRoomGameMode::ChangeLaserGameState(EKGameState NewLaserGameState)
{
	if (LaserGameState == NewLaserGameState) { return; }
	
	LaserGameState = NewLaserGameState;

	switch (LaserGameState)
	{
	case EKGameState::NONE:
		break;
	case EKGameState::START:
	{
		SpawnStageActor();
		break;
	}
	case EKGameState::INGAME:
		break;
	case EKGameState::CLEAR:
	{
		if (Stage == MaxStage)
		{
			ChangeLaserGameState(EKGameState::FINISH);
			return;
		}
		else
		{
			//ResetStageActor();
			//Stage++;
			//SetDisplay();
			//SpawnStageActor();
			LaserGameState = EKGameState::INGAME;
		}
		break;
	}
	case EKGameState::FINISH:
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
	

	ChangeLaserGameState(EKGameState::START);
	//GetWorld()->GetTimerManager().SetTimer(LaserGameStateTimerHandle,
	//	FTimerDelegate::CreateLambda([this]()
	//		{
	//			ChangeLaserGameState(EKGameState::START);
	//		}), 2.0f, false);
	
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
	OpenDoorIndex = StageData->OpenDoorIndex;
	SpawnedActors.Empty();
	for (auto& data : StageData->LaserRoomActorDatas)
	{
		if (!data.ActorClass) return;
		FTransform SpawnTr;

		SpawnTr.SetLocation(data.SpawnLocation);
		SpawnTr.SetRotation(data.SpawnRotation.Quaternion());
		SpawnTr.SetScale3D(data.SpawnScale);

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
			data.ActorClass,
			SpawnTr,
			SpawnParams
		);

		if (SpawnedActor->IsA<ALRoom>())
		{
			CurentRoom = Cast<ALRoom>(SpawnedActor);
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

void ALaserRoomGameMode::OpenDoor()
{
	if (CurentRoom)
	{
		CurentRoom->OpenDoor(OpenDoorIndex);
	}
}
