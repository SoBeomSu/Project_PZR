// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/LaserRoom/EndLaserPoint.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "KJW/LaserRoom/Textboard.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "KJW/LaserRoom/LaserRoomGameMode.h"
#include "KJW/LaserRoom/StartLaserPoint.h"
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

	LaserGamemode = Cast<ALaserRoomGameMode>(GetWorld()->GetAuthGameMode());
	if (LaserGamemode)
	{
		GoalCount = LaserGamemode->NeedLaser;
	}

	if (UUserWidget* Widget = TextWidget->GetWidget())
	{
		Textboard = Cast<UTextboard>(Widget);
		SetGoalText();
	}

}

// Called every frame
void AEndLaserPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetGoalMt(DeltaTime);
}

void AEndLaserPoint::AddMirrorPoint(AStartLaserPoint* StartLaserPoint)
{
	if (StartLasers.Contains(StartLaserPoint)) return;

	StartLasers.Add(StartLaserPoint);

	SetGoalInfo();
}

void AEndLaserPoint::RemoveMirrorPoint(AStartLaserPoint* StartLaserPoint)
{
	if (!StartLasers.Contains(StartLaserPoint)) return;

	StartLasers.Remove(StartLaserPoint);

	SetGoalInfo();
}

void AEndLaserPoint::SetGoalInfo()
{
	SetGoalText();
}

void AEndLaserPoint::SetGoalMt(const float& DeltaTime)
{
	bool bSucceed = StartLasers.Num() == GoalCount ? true : false;

	if (bSucceed)
	{
		CurNeedTime += DeltaTime;
	}
	else
	{
		CurNeedTime -= DeltaTime;	
	}
	
	CurNeedTime = FMath::Clamp(CurNeedTime , 0.0f, NeedTime);
	
	float Delta = CurNeedTime / NeedTime;
	if (CurNeedTime > NeedTime) { Delta = 1.0f; }

	FLinearColor InColor = FLinearColor::Black;
	EmissiveScale = FMath::Lerp(1.0f, 10.0f, Delta);
	InColor = FMath::Lerp(InColor, FLinearColor::White, Delta);

	MeshComp->SetScalarParameterValueOnMaterials(TEXT("EmissiveScale"), EmissiveScale);
	MeshComp->SetColorParameterValueOnMaterials(TEXT("Color"), InColor);

	if(LaserGamemode && CurNeedTime >= NeedTime)
	{
		LaserGamemode->ChangeLaserGameState(ELaserGameState::CLEAR);
	}
}


void AEndLaserPoint::SetGoalText()
{
	if (!Textboard) return;
	int32 num = GoalCount - StartLasers.Num();
	Textboard->SetTextBlock((FText::AsNumber(num)));
	
}



