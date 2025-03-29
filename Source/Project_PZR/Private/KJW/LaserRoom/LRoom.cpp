// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LRoom.h"
#include "Components/ChildActorComponent.h"
#include "KJW/LaserRoom/LDoor.h"
#include "KJW/LaserRoom/LaserRoomGameMode.h"


// Sets default values
ALRoom::ALRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RoomSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RoomSceneComp"));
	SetRootComponent(RoomSceneComp);

	L_Door = CreateDefaultSubobject<UChildActorComponent>(TEXT("L_Door"));
	L_Door->SetupAttachment(GetRootComponent());
	R_Door = CreateDefaultSubobject<UChildActorComponent>(TEXT("R_Door"));
	R_Door->SetupAttachment(GetRootComponent());
	F_Door = CreateDefaultSubobject<UChildActorComponent>(TEXT("F_Door"));
	F_Door->SetupAttachment(GetRootComponent());
	B_Door = CreateDefaultSubobject<UChildActorComponent>(TEXT("B_Door"));
	B_Door->SetupAttachment(GetRootComponent());

	RoomBase = CreateDefaultSubobject<UChildActorComponent>(TEXT("RoomBase"));
	RoomBase->SetupAttachment(GetRootComponent());
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

void ALRoom::OpenDoor(int32 Index)
{
	if (Index < 0 || Index >= Doors.Num()) return;

	Doors[Index]->SetDoor(true);

	if (NextRoom)
	{

	}
	
}

void ALRoom::CloseDoor(int32 Index)
{
	if (Index < 0 || Index >= Doors.Num()) return;
	
	Doors[Index]->SetDoor(false);
}

