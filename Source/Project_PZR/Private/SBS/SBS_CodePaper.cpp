// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_CodePaper.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "MotionControllerComponent.h"

// Sets default values
ASBS_CodePaper::ASBS_CodePaper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BoxCollision;
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    BoxCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void ASBS_CodePaper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBS_CodePaper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBS_CodePaper::StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight)
{
	BoxCollision->SetSimulatePhysics(false);
	this->AttachToComponent(MontionComp, FAttachmentTransformRules::KeepWorldTransform);
}

void ASBS_CodePaper::StopGrab(class UMotionControllerComponent* MontionComp, bool IsRight)
{
	BoxCollision->SetSimulatePhysics(true);
	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void ASBS_CodePaper::UpdateTextDisplay()
{

}
