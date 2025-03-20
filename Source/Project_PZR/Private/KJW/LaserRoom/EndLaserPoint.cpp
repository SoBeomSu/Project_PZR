// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/LaserRoom/EndLaserPoint.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "KJW/LaserRoom/Textboard.h"

// Sets default values
AEndLaserPoint::AEndLaserPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	SetRootComponent(BoxComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshObj.Succeeded()) MeshComp->SetStaticMesh(MeshObj.Object);


	BoxComp->SetBoxExtent(FVector(50.0f, 6.5f, 50.0f));
	MeshComp->SetRelativeScale3D(FVector(1.0f, 0.1f, 1.0f));

	//UI Component
	TextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextWidget"));
	TextWidget->SetupAttachment(RootComponent);
	TextWidget->SetRelativeLocationAndRotation(FVector(0.0f, 6.0f, 0.0f), FRotator(0.0f, 90.0f, 0.0f));

	ConstructorHelpers::FClassFinder<UTextboard> TextClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_Project/KJW/LaserRoom/UI/BPW_EndLaser.BPW_EndLaser_C'"));
	if (TextClass.Succeeded()) TextWidget->SetWidgetClass(TextClass.Class);

}


// Called when the game starts or when spawned
void AEndLaserPoint::BeginPlay()
{
	Super::BeginPlay();

	if (FailMaterial)
	{
		MeshComp->SetMaterial(0, FailMaterial);
	}

	if(UUserWidget* Widget = TextWidget->GetWidget())
	{
		Textboard = Cast<UTextboard>(Widget);
		SetGoalText();
	}
}

// Called every frame
void AEndLaserPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndLaserPoint::SetGoalInfo()
{
	SetGoalText();
	SetGoalMt();
}

void AEndLaserPoint::SetGoalMt()
{
	this->bSucceed = Mirrors.Num() == GoalCount ? true : false;

	// 현재 상태에 따라 적절한 머티리얼 선택
	UMaterialInterface* NewMaterial = this->bSucceed ? SuccessMaterial : FailMaterial;
	if (NewMaterial)
	{
		MeshComp->SetMaterial(0, NewMaterial);
	}
}

void AEndLaserPoint::AddMirrorPoint(ALaserMirror* LaserMirror)
{
	if (Mirrors.Contains(LaserMirror)) return;

	Mirrors.Add(LaserMirror);

	SetGoalInfo();
}

void AEndLaserPoint::RemoveMirrorPoint(ALaserMirror* LaserMirror)
{
	if (!Mirrors.Contains(LaserMirror)) return;

	Mirrors.Remove(LaserMirror);

	SetGoalInfo();
}

void AEndLaserPoint::SetGoalText()
{
	if (!Textboard) return;
	int32 num = GoalCount - Mirrors.Num();
	Textboard->SetTextBlock((FText::AsNumber(num)));
	
}



