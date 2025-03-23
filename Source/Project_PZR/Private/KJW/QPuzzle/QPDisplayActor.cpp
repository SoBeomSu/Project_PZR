// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/QPuzzle/QPDisplayActor.h"
#include "Components/WidgetComponent.h"

#include "KJW/QPuzzle/QPuzzleGameMode.h"
#include "KJW/QPuzzle/QPDisplay.h"
// Sets default values
AQPDisplayActor::AQPDisplayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(SceneComp);

	//UI Component
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(RootComponent);
	WidgetComp->SetRelativeLocationAndRotation(FVector(0.0f), FRotator(0.0f, 90.0f, 0.0f));

	WidgetComp->SetDrawAtDesiredSize(true);

	ConstructorHelpers::FClassFinder<UQPDisplay> Displayclass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_Project/KJW/02_QPuzzleRoom/UI/BPW_QPDisplay.BPW_QPDisplay_C'"));
	if (Displayclass.Succeeded()) WidgetComp->SetWidgetClass(Displayclass.Class);
}

// Called when the game starts or when spawned
void AQPDisplayActor::BeginPlay()
{
	Super::BeginPlay();

	QPGM = Cast<AQPuzzleGameMode>(GetWorld()->GetAuthGameMode());
	if (UUserWidget* Widget = WidgetComp->GetWidget())
	{
		UQPDisplay* Display = Cast<UQPDisplay>(Widget);
		Display->QPGM = QPGM;
		QPDisplay = Display;
	}

	QPGM->UpdateStageDelegate.AddUObject(this, &ThisClass::SetDisplay);
	QPGM->UpdateAnswerDelegate.AddUObject(this, &ThisClass::SetAnswer);

}

// Called every frame
void AQPDisplayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AQPDisplayActor::SetAnswerText(FText text)
{
	QPDisplay->SetAnswerText(text);
}

void AQPDisplayActor::SetDisplay(EKGameState LaserGameState)
{
	QPDisplay->SetDisplay(LaserGameState);
}

void AQPDisplayActor::SetAnswer(EKGameState LaserGameState)
{
	FText Answer = QPGM->GetAnswerText();
	QPDisplay->SetAnswerText(Answer);
}

