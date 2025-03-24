// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/QPuzzle/QPuzzlePadActor.h"
#include "KJW/QPuzzle/QPuzzleGameMode.h"
#include "KJW/QPuzzle/QPuzzlePad.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"


// Sets default values
AQPuzzlePadActor::AQPuzzlePadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(5.0f , 110.0f, 65.0f));


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeScale3D(FVector(0.1f, 2.1f, 1.2f));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (Mesh.Succeeded()) MeshComp->SetStaticMesh(Mesh.Object);


	//UI Component
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(RootComponent);
	WidgetComp->SetRelativeLocation(FVector(5.1f, 0.0f, 0.0f));
	WidgetComp->SetRelativeLocationAndRotation(FVector(0.0f), FRotator(0.0f, 90.0f, 0.0f));
	//WidgetComp->SetDrawAtDesiredSize(true);
	WidgetComp->SetDrawSize(FVector2D(2000.0f,1000.0f));
	
	ConstructorHelpers::FClassFinder<UQPuzzlePad> Displayclass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_Project/KJW/02_QPuzzleRoom/UI/BPW_QPPad.BPW_QPPad_C'"));
	if (Displayclass.Succeeded()) WidgetComp->SetWidgetClass(Displayclass.Class);
}

// Called when the game starts or when spawned
void AQPuzzlePadActor::BeginPlay()
{
	Super::BeginPlay();


	QPGM = Cast<AQPuzzleGameMode>(GetWorld()->GetAuthGameMode());
	if (UUserWidget* Widget = WidgetComp->GetWidget())
	{
		QPPad = Cast<UQPuzzlePad>(Widget);
		if (QPPad)
		{
			QPPad->QPGM = QPGM;
		}

		QPGM->UpdateStageDelegate.AddUObject(this, &ThisClass::SetDisplay);
		QPGM->UpdateAnswerDelegate.AddUObject(this, &ThisClass::UpdateAnswerDisplay);
	}


	
}

void AQPuzzlePadActor::StartGrab(AActor* HandActor)
{
		// HandActor¿¡ ºÎÂø
		AttachToActor(HandActor, FAttachmentTransformRules::KeepWorldTransform);
}

void AQPuzzlePadActor::StopGrab(AActor* HandActor)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void AQPuzzlePadActor::RotObject(const FRotator AddRotator)
{
	AddActorLocalRotation(AddRotator);
}

void AQPuzzlePadActor::SetDisplay(EKGameState LaserGameState)
{
	QPPad->SetDisplay(LaserGameState);

}

void AQPuzzlePadActor::UpdateAnswerDisplay(EKGameState LaserGameState)
{
	QPPad->SetDisplay(LaserGameState);
}

