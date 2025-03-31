// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LaserRoomGameMode.h"
#include "KJW/LaserRoom/LaserStageData.h"
#include "KJW/LaserRoom/Laser.h"
#include "KJW/LaserRoom/LRStatgeDisplay.h"
#include "KJW/LaserRoom/LRoom.h"
#include "KJW/StageObject.h"


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
		//SpawnStageActor();
		//Stage++;
		//SpawnStageActor();
		SpanwStage();
		RoomList[CurStage]->StartRoom();
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
	
	CurStage = 0;
	ChangeLaserGameState(EKGameState::START);
	//GetWorld()->GetTimerManager().SetTimer(LaserGameStateTimerHandle,
	//	FTimerDelegate::CreateLambda([this]()
	//		{
	//			ChangeLaserGameState(EKGameState::START);
	//		}), 2.0f, false);
	
}

void ALaserRoomGameMode::ResetStageActor()
{
	for (int i = 0; i < SpawnedActors.Num(); i++)
	{
		SpawnedActors[i]->Destroy();
	}
	
	SpawnedActors.Empty();
}

void ALaserRoomGameMode::SpanwStage()
{
	if (StageDatas.IsEmpty()) return;
	int32 index = Stage - 1;
	
	//시작 위치 부터 맵 생성 하기
	for (int32 i = index; i < StageDatas.Num(); ++i)
	{
		//스테이지 정보 가져오기
		ULaserStageData* StageData = StageDatas[i];

		// 스폰 파라미터 설정
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//메인 룸 생성
		ALRoom* LRoom = GetWorld()->SpawnActor<ALRoom>(
			LaserRoomClass,
			RoomSpawnPos, FRotator(),
			SpawnParams
		);
		if(!LRoom) return;
		if (PrevRoom)
		{
			LRoom->PrevRoom = PrevRoom;
			PrevRoom->NextRoom = LRoom;
		}
		PrevRoom = LRoom;
		
		//스테이지 오브젝트 스폰하기
		NeedLaser = StageData->NeedLaser;
		SpawnedActors.Empty();
		LRoom->OpenDoorIndex = StageData->OpenDoorIndex;
		for (auto& data : StageData->LaserRoomActorDatas)
		{
			if (!data.ActorClass) return;
			FTransform SpawnTr;

			//룸 기준으로 오브젝트 위치 생성
			FVector SpawnPos = data.SpawnLocation + RoomSpawnPos;

			SpawnTr.SetLocation(SpawnPos);
			SpawnTr.SetRotation(data.SpawnRotation.Quaternion());
			SpawnTr.SetScale3D(data.SpawnScale);

			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
				data.ActorClass,
				SpawnTr,
				SpawnParams
			);

			if (IStageObject* stageObj = Cast<IStageObject>(SpawnedActor))
			{
				LRoom->StageObject.Add(stageObj);
			}
			
			LRoom->RoomObject.Add(SpawnedActor);
		}

		//다음 스테이지 스폰위치
		//2935.0
		int x[4] = { 0,0,1,-1 };
		int y[4] = { -1,1,0,0 };
		RoomSpawnPos += FVector(x[LRoom->OpenDoorIndex] * 2935.0f, y[LRoom->OpenDoorIndex] * 2935.0f, 0.0f);
		RoomList.Add(LRoom);
	}
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

	ALRoom* CurentRoom = RoomList[CurStage];
	if (CurentRoom)
	{
		CurentRoom->IsRoomClear = true;
		CurentRoom->OpenDoor();
		CurStage++;
		
	}
}
