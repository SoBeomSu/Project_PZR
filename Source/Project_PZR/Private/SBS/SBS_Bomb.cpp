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
		UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(*Name); //Number1 Number2
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

void ASBS_Bomb::OnButtonPressed(FHitResult& HitResult, EVRButton VRButton)
{

	if (HitResult.GetComponent())
	{
		UBoxComponent* HitBox = Cast<UBoxComponent>(HitResult.GetComponent());
		if (HitBox && NumberCollisions.Contains(HitBox))
		{
			FName Tag = HitBox->ComponentTags[0];
			int Number = FCString::Atoi(*Tag.ToString());
			switch (Number)
			{
				case 1:
					EnterPassword(Number);
				break;
				case 2:
					EnterPassword(Number);
				break;
				case 3:
					EnterPassword(Number);
				break;
				case 4:
					EnterPassword(Number);
				break;
				case 5:
					EnterPassword(Number);
				break;
				case 6:
					EnterPassword(Number);
				break;
				case 7:
					EnterPassword(Number);
				break;
				case 8:
					EnterPassword(Number);
				break;
				case 9:
					EnterPassword(Number);
				break;
			}
		}
	}
}

FString ASBS_Bomb::EnterPassword(int Numbers)
{
	FString Password;

	//Queue


	return Password;
}

