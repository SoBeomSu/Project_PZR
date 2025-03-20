// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/LaserRoom/EndLaserPoint.h"
#include "Components/BoxComponent.h"

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
}


// Called when the game starts or when spawned
void AEndLaserPoint::BeginPlay()
{
	Super::BeginPlay();

	if (FailMaterial)
	{
		MeshComp->SetMaterial(0, FailMaterial);
	}
	
}

// Called every frame
void AEndLaserPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	SetGoalMt();
}

void AEndLaserPoint::RemoveMirrorPoint(ALaserMirror* LaserMirror)
{
	if (!Mirrors.Contains(LaserMirror)) return;

	Mirrors.Remove(LaserMirror);

	SetGoalMt();
}



