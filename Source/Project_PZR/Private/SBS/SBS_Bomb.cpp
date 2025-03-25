// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_Bomb.h"

// Sets default values
ASBS_Bomb::ASBS_Bomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	for (int i= 1; i <= 9; i++)
	{
		FString Name = FString::Printf(TEXT("Number%d"), i);
		UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(*Name);
		Box->SetupAttachment(StaticMesh);
		Box->SetCollisionProfileName(TEXT("DefualtObject")); // 충돌 설정
		Box->ComponentTags.Add(FName(*FString::FromInt(i))); // 태그로 숫자 지정
		NumberCollisions.Add(Box);
	}
}

// Called when the game starts or when spawned
void ASBS_Bomb::BeginPlay()
{
	Super::BeginPlay();
	SetupKeypad();
}

// Called every frame
void ASBS_Bomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASBS_Bomb::SetupKeypad()
{

}

