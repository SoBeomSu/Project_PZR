// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LDoor.h"

// Sets default values
ALDoor::ALDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("DoorSceneComp"));
	SetRootComponent(DoorSceneComp);

	L_DoorComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("L_DoorComp"));
	L_DoorComp->SetupAttachment(GetRootComponent());

	R_DoorComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_DoorComp"));
	R_DoorComp->SetupAttachment(GetRootComponent());

	
	L_DoorComp->SetRelativeLocation(FVector(-83.0f , 5.0f ,32.0f));
	R_DoorComp->SetRelativeLocation(FVector(83.0f , 5.0f ,32.0f));
}

// Called when the game starts or when spawned
void ALDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorTick(DeltaTime);
}

void ALDoor::SetDoor(bool Open)
{
	bOpen = Open;
}

void ALDoor::DoorTick(float DeltaTime)
{
	if (DoorTime <= 0) return;
		
	
	if (bOpen)
		DoorTimer += DeltaTime;
	else
		DoorTimer -= DeltaTime;

	DoorTimer =	FMath::Clamp(DoorTimer, 0.0f, DoorTime);
	float percent = DoorTimer / DoorTime;

	FVector LDoorPos =  FMath::Lerp(LDoor_ClosePos, LDoor_OpenPos, percent);
	FVector RDoorPos =  FMath::Lerp(RDoor_ClosePos, RDoor_OpenPos, percent);
	
	L_DoorComp->SetRelativeLocation(LDoorPos);
	R_DoorComp->SetRelativeLocation(RDoorPos);

}

