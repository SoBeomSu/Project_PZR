// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LRoom.h"
#include "Components/ChildActorComponent.h"
#include "Components/BoxComponent.h"
#include "KJW/LaserRoom/LDoor.h"
#include "KJW/LaserRoom/LaserRoomGameMode.h"


// Sets default values
ALRoom::ALRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RoomSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RoomSceneComp"));
	SetRootComponent(RoomSceneComp);

	Main_BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Main_BoxComp"));
	Main_BoxComp->SetupAttachment(GetRootComponent());

	L_Door = CreateDefaultSubobject<UChildActorComponent>(TEXT("L_Door"));
	L_Door->SetupAttachment(GetRootComponent());
	L_BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("L_BoxComp"));
	L_BoxComp->SetupAttachment(L_Door);

	R_Door = CreateDefaultSubobject<UChildActorComponent>(TEXT("R_Door"));
	R_Door->SetupAttachment(GetRootComponent());
	R_BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("R_BoxComp"));
	R_BoxComp->SetupAttachment(R_Door);

	F_Door = CreateDefaultSubobject<UChildActorComponent>(TEXT("F_Door"));
	F_Door->SetupAttachment(GetRootComponent());
	F_BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("F_BoxComp"));
	F_BoxComp->SetupAttachment(F_Door);

	B_Door = CreateDefaultSubobject<UChildActorComponent>(TEXT("B_Door"));
	B_Door->SetupAttachment(GetRootComponent());
	B_BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("B_BoxComp"));
	B_BoxComp->SetupAttachment(B_Door);

	RoomBase = CreateDefaultSubobject<UChildActorComponent>(TEXT("RoomBase"));
	RoomBase->SetupAttachment(GetRootComponent());


	L_BoxComp->SetBoxExtent(FVector(200.0f, 32.0f, 32.0f));
	L_BoxComp->SetRelativeLocation(FVector(0.0f, 230.0f , 100.0f));
	R_BoxComp->SetBoxExtent(FVector(200.0f, 32.0f, 32.0f));
	R_BoxComp->SetRelativeLocation(FVector(0.0f, 230.0f, 100.0f));
	F_BoxComp->SetBoxExtent(FVector(200.0f, 32.0f, 32.0f));
	F_BoxComp->SetRelativeLocation(FVector(0.0f, 230.0f, 100.0f));
	B_BoxComp->SetBoxExtent(FVector(200.0f, 32.0f, 32.0f));
	B_BoxComp->SetRelativeLocation(FVector(0.0f, 230.0f, 100.0f));


	L_BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OverLapDoorBoxComp);
	R_BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OverLapDoorBoxComp);
	F_BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OverLapDoorBoxComp);
	B_BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OverLapDoorBoxComp);
	Main_BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OverLapMainBoxComp);
}

// Called when the game starts or when spawned
void ALRoom::BeginPlay()
{
	Super::BeginPlay();

	LRGM = Cast<ALaserRoomGameMode>(GetWorld()->GetAuthGameMode());
	if (LRGM)
	{
		
	}

	Doors.Empty();
	Doors.Add(Cast<ALDoor>(L_Door->GetChildActor()));
	Doors.Add(Cast<ALDoor>(R_Door->GetChildActor()));
	Doors.Add(Cast<ALDoor>(F_Door->GetChildActor()));
	Doors.Add(Cast<ALDoor>(B_Door->GetChildActor()));
}

// Called every frame
void ALRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALRoom::StartRoom()
{
	if (!IsStart)
	{
		for (IStageObject* interface : StageObject)
		{
			interface->Start();
		}
		IsStart = true;
	}
}

void ALRoom::OpenDoor(int32 Index)
{
	Doors[Index]->SetDoor(true);
}

void ALRoom::OpenDoor()
{
	if (OpenDoorIndex < 0 || OpenDoorIndex >= Doors.Num()) return;
	
	OpenDoor(OpenDoorIndex);
	

	if (NextRoom && IsRoomClear)
	{
		int32 nextDoor[4] = {1,0,3,2 };
		NextRoom->OpenDoor(nextDoor[OpenDoorIndex]);

	}
}

void ALRoom::CloseDoor(int32 Index)
{
	if (Index < 0 || Index >= Doors.Num()) return;
	
	Doors[Index]->SetDoor(false);
}

void ALRoom::CloseAllDoor()
{
	for (ALDoor* door : Doors)
	{
		door->SetDoor(false);
	}
}

void ALRoom::DestroyObjecet()
{
	for (AActor* obj : RoomObject)
	{
		obj->Destroy();
	}
}

void ALRoom::OverLapDoorBoxComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsRoomClear)
		CloseAllDoor();
	
}

void ALRoom::OverLapMainBoxComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsRoomClear)
		CloseAllDoor();
	if (PrevRoom)
	{
		PrevRoom->DestroyObjecet();
		PrevRoom = nullptr;
	}
	
	StartRoom();

}

