// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/LaserRoom/LRDisplayActor.h"
#include "Components/WidgetComponent.h"

#include "KJW/LaserRoom/LRDisplay.h"
#include "KJW/LaserRoom/LaserRoomGameMode.h"

// Sets default values
ALRDisplayActor::ALRDisplayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(SceneComp);

	//UI Component
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(RootComponent);
	WidgetComp->SetRelativeLocationAndRotation(FVector(0.0f), FRotator(0.0f, 90.0f, 0.0f));

	ConstructorHelpers::FClassFinder<ULRDisplay> LRDisplayclass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_Project/KJW/LaserRoom/UI/BPW_LRDisplay.BPW_LRDisplay_C'"));
	if (LRDisplayclass.Succeeded()) WidgetComp->SetWidgetClass(LRDisplayclass.Class);

}

// Called when the game starts or when spawned
void ALRDisplayActor::BeginPlay()
{
	Super::BeginPlay();

	ALaserRoomGameMode* LRGM = Cast<ALaserRoomGameMode>(GetWorld()->GetAuthGameMode());
	

	if (UUserWidget* Widget = WidgetComp->GetWidget())
	{
		LRDisplay = Cast<ULRDisplay>(Widget);
		LRDisplay->LRGM = LRGM;
	
	}
	LRGM->UpdateStageDelegate.AddUObject(this, &ThisClass::SetDisplay);
}

void ALRDisplayActor::SetDisplay(ELaserGameState LaserGameState)
{
	if (!LRDisplay)return;
	LRDisplay->SetDisplay(LaserGameState);
}


