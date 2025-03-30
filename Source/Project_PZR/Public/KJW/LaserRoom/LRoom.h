// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KJW/StageObject.h"
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
	void StartRoom();
	void OpenDoor(int32 Index);
	void OpenDoor();
	void CloseDoor(int32 Index);
	void CloseAllDoor();
	void DestroyObjecet();
private :
	UFUNCTION()
	void OverLapDoorBoxComp ( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OverLapMainBoxComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	ALRoom* NextRoom;
	ALRoom* PrevRoom;
	TArray<AActor*> RoomObject;
	TArray<IStageObject*> StageObject;
public:
	bool IsRoomClear = false;
	int32 OpenDoorIndex = 0;
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

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UBoxComponent* Main_BoxComp;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UBoxComponent* L_BoxComp;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UBoxComponent* R_BoxComp;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UBoxComponent* F_BoxComp;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UBoxComponent* B_BoxComp;

	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* RoomBase;

	TArray<class ALDoor*> Doors;

	class ALaserRoomGameMode* LRGM;

	bool IsStart = false;


};
