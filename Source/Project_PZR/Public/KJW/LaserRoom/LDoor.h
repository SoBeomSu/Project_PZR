// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LDoor.generated.h"

UCLASS()
class PROJECT_PZR_API ALDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetDoor(bool Open);
private:
	void DoorTick(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	USceneComponent* DoorSceneComp;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* L_DoorComp;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* R_DoorComp;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	bool bOpen = false;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float DoorTime = 0.5f;

	float DoorTimer = 0.0f;
	
	FVector LDoor_OpenPos = FVector(-164.0f, 5.0f, 32.0f);
	FVector RDoor_OpenPos = FVector(164.0f, 5.0f, 32.0f);

	FVector LDoor_ClosePos = FVector(-83.0, 5.0f, 32.0f);
	FVector RDoor_ClosePos = FVector(83.0f, 5.0f, 32.0f);
	


};
