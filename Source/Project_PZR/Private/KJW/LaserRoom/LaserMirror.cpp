// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LaserMirror.h"

// Sets default values
ALaserMirror::ALaserMirror()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALaserMirror::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserMirror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

