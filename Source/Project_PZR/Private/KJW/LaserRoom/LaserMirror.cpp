// Fill out your copyright notice in the Description page of Project Settings.
#include "KJW/LaserRoom/LaserMirror.h"
#include "KJW/KHelper.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraSystem.h"


#include "KJW/LaserRoom/EndLaserPoint.h"
// Sets default values
ALaserMirror::ALaserMirror()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	SetRootComponent(BoxComp);

	MirrorComp = CreateDefaultSubobject<UStaticMeshComponent>("MirrorComp");
	MirrorComp->SetupAttachment(RootComponent);



	BottomComp = CreateDefaultSubobject<UStaticMeshComponent>("BottomComp");
	BottomComp->SetupAttachment(RootComponent);
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mirror(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (Mirror.Succeeded()) MirrorComp->SetStaticMesh(Mirror.Object);

	ConstructorHelpers::FObjectFinder<UStaticMesh> Bottom(TEXT("/Script/Engine.StaticMesh'/Engine/VREditor/LaserPointer/CursorPointer.CursorPointer'"));
	if (Bottom.Succeeded()) BottomComp->SetStaticMesh(Bottom.Object);

	BoxComp->SetBoxExtent(FVector(50.0f, 6.5f, 70.0f));

	MirrorComp->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	MirrorComp->SetRelativeScale3D(FVector(1.0f, 0.1f, 1.0f));

	BottomComp->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
	BottomComp->SetRelativeScale3D(FVector(0.5f, 0.2f, 0.2f));
	BottomComp->SetRelativeRotation(FRotator(90.0f,0.0f, 0.0f));

}

// Called when the game starts or when spawned
void ALaserMirror::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserMirror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ALaserMirror::NextLaserStart(const FHitResult& HitInfo, const FVector& InDir, const float& LaserLength, TArray<FVector>& Lines, bool& IsGoal)
{
	//1. ���� �������� �ݻ� ���� ���ϱ�
	FVector SurfaceNormal = HitInfo.ImpactNormal;
	FVector StartPoint = HitInfo.Location;
	FVector ReflectionVector = KHelper::GetReflectionVector(InDir, SurfaceNormal);

	//2. ���� ���� ������ ��ġ ���ϱ�
	//FVector ReflectionVector = InDir.MirrorByVector(SurfaceNormal);
	FVector EndPoint = StartPoint + (ReflectionVector * LaserLength);

	//3.���� Ʈ���̽��� ���� �浹ü Ȯ��
	FHitResult MirrorHitInfo;
	ALaserMirror* NextMirror = nullptr;
	IsGoal = false;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(MirrorHitInfo, StartPoint, EndPoint, ECC_GameTraceChannel1
		, Params);

	if (bHit)
	{
		FVector Hitpoint = MirrorHitInfo.Location;
		EndPoint = Hitpoint;
		NextMirror = Cast<ALaserMirror>(MirrorHitInfo.GetActor());

		//���� �浹ü�� ��ǥ �����̶��
		AEndLaserPoint* Goal = Cast<AEndLaserPoint>(MirrorHitInfo.GetActor());
		if (Goal) { IsGoal = true; }
		
	}
	
	Lines.Add(EndPoint);

	if (NextMirror)
	{
		NextMirror->NextLaserStart(MirrorHitInfo, ReflectionVector, LaserLength, Lines, IsGoal);
	}


	if (bDrawLaser)
	{
		//Ȯ�ο� ����� ����
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red);
		DrawDebugLine(GetWorld(), StartPoint, StartPoint + SurfaceNormal * 500.0f, FColor::Black);
	}
}


void ALaserMirror::StartGrab(AActor* HandActor)
{
	// HandActor�� ����
	AttachToActor(HandActor, FAttachmentTransformRules::KeepWorldTransform);
}

void ALaserMirror::StopGrab(AActor* HandActor)
{
	// HandActor�κ��� �и�
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void ALaserMirror::RotObject(const FRotator AddRotator)
{
	AddActorLocalRotation(AddRotator);
}







