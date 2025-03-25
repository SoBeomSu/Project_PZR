// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_GameStartButton.h"

// Sets default values
ASBS_GameStartButton::ASBS_GameStartButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Pillar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pillar"));
	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Button->SetupAttachment(Pillar);

}

// Called when the game starts or when spawned
void ASBS_GameStartButton::BeginPlay()
{
	Super::BeginPlay();
	GameMode01 = Cast<ASBS_GameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void ASBS_GameStartButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if ((GameMode01->bStartGame)&&(!bworked))
	//{
	//	DelayTime+=DeltaTime;
	//	if (DeltaTime > 2)
	//	{
	//		Lightswitch->SwitchOff();
	//		bworked = true;
	//	}
	//}
}

void ASBS_GameStartButton::ButtonPressed()
{
	Button->SetRelativeLocation(FVector(0, 0, -10));
	if (GameMode01)
	{
		GameMode01->StartGame();
	}
}

void ASBS_GameStartButton::StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight)
{
	ButtonPressed();
}

