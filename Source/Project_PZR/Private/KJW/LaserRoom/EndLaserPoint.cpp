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

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	SetRootComponent(MeshComp);

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetupAttachment(RootComponent);


	//UI Component
	TextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextWidget"));
	TextWidget->SetupAttachment(RootComponent);
	TextWidget->SetRelativeLocationAndRotation(FVector(0.0f, 6.0f, 0.0f), FRotator(0.0f, 90.0f, 0.0f));

	ConstructorHelpers::FClassFinder<UTextboard> TextClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/A_Project/KJW/01_LaserRoom/UI/BPW_EndLaser.BPW_EndLaser_C'"));
	if (TextClass.Succeeded()) TextWidget->SetWidgetClass(TextClass.Class);


	BoxComp->SetCollisionProfileName(TEXT("Mirror"));
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

	//SetGoalMt(DeltaTime);
}

void AEndLaserPoint::OnButtonPressed(FHitResult& HitResult, EVRButton VRButton)
{
	if (VRButton == EVRButton::Left_X_Button)
	{
		if (IsOpen)return;

		int32 num = GoalCount - StartLasers.Num();
		if (num == 0)
		{
			IsOpen = true;
			LaserGamemode->OpenDoor();
		}
	}
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

	//if(LaserGamemode && CurNeedTime >= NeedTime)
	//{
	//	LaserGamemode->ChangeLaserGameState(EKGameState::CLEAR);
	//}
}


void AEndLaserPoint::SetGoalText()
{
	if (!Textboard) return;
	int32 num = GoalCount - StartLasers.Num();
	if (num == 0)
	{
		Textboard->SetTextBlock(FText::FromString("Complete"));
	}
	else
	{
		Textboard->SetTextBlock(FText::FromString("Ready"));
	}
	
	//Textboard->SetTextBlock((FText::AsNumber(num)));
	
}



