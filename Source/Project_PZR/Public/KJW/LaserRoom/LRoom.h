// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LRoom.generated.h"

UCLASS()
class PROJECT_PZR_API ALRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	void OpenDoor(int32 Index);
	void CloseDoor(int32 Index);

	ALRoom* NextRoom;
	ALRoom* PreRoom;
private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	USceneComponent* RoomSceneComp;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UChildActorComponent* L_Door;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UChildActorComponent* R_Door;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UChildActorComponent* F_Door;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UChildActorComponent* B_Door;

	TArray<class ALDoor*> Doors;

	class ALaserRoomGameMode* LRGM;

};
