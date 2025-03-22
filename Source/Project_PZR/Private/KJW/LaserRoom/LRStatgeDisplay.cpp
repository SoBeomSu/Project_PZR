// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/LaserRoom/LRStatgeDisplay.h"
#include "Components/TextRenderComponent.h"
#include "KJW/LaserRoom/LaserRoomGameMode.h"

// Sets default values
ALRStatgeDisplay::ALRStatgeDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(SceneComp);

	TextComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComp"));
	TextComp->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ALRStatgeDisplay::BeginPlay()
{
	Super::BeginPlay();
	
	LRGM = Cast<ALaserRoomGameMode>(GetWorld()->GetAuthGameMode());
	LRGM->SetDisplayGmae(this);
}



void ALRStatgeDisplay::SetStageInfo()
{
	if (!LRGM) return;

	int32 curStage = LRGM->GetCurentStage();

	if (LRGM->LaserGameState == ELaserGameState::FINISH)
	{
		TextComp->SetText(FText::FromString("FINISH..."));
	}
	else
	{
		FString str = "Stage - " + curStage;
		TextComp->SetText(FText::FromString(str));
	}


}

