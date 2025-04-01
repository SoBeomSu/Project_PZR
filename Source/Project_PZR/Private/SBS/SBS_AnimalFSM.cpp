// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_AnimalFSM.h"
#include "SBS/SBS_Animal.h"
#include "SBS/SBS_FirePit.h"
#include "Kismet/GameplayStatics.h"
#include "SBS/SBS_GameMode.h"
#include "MotionControllerComponent.h"
#include "SBS/SBS_AnimalAnim.h"

// Sets default values for this component's properties
USBS_AnimalFSM::USBS_AnimalFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USBS_AnimalFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GameMode = Cast<ASBS_GameMode>(GetWorld()->GetAuthGameMode());
	Animal = Cast<ASBS_Animal>(GetOwner());
	AnimalAnim = Cast<USBS_AnimalAnim>(Animal->SkeletalMesh->GetAnimInstance());
	TArray<AActor*> Animals;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASBS_Animal::StaticClass(), Animals);
	for (AActor* Actor : Animals)
	{
		ASBS_Animal* OtherAnimal = Cast<ASBS_Animal>(Actor);
		if (OtherAnimal && OtherAnimal->bIsLeader)
		{
			LeaderAnimal = OtherAnimal;
			break;
		}
	}
}


// Called every frame
void USBS_AnimalFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	switch (mState)
	{
	case ESBS_AnimalState::Stay: Stay(DeltaTime); break;
	case ESBS_AnimalState::Idle: IdleState(); break;
	case ESBS_AnimalState::Move: MoveState(); break;
	case ESBS_AnimalState::InAir: InAir(); break;
	case ESBS_AnimalState::Burning: Burning(); break;
	case ESBS_AnimalState::Dead: Dead(); break;
	}
	//if (bCrash)
	//{
	//	ChangeDir();
	//	bCrash = true;
	//}
	if (bIsScaling)
	{
		ScaleTime += DeltaTime;
		float t = FMath::Clamp(ScaleTime / ScaleDuration, 0.0f, 1.0f); //진행도
		float ElasticValue = FMath::Pow(2.0f, -10.0f * (1.0f - t)) * FMath::Sin((t - 0.1f) * 2.0f * PI / 0.3f); // 크기 수식
		float ScaleFactor = MaxScale - (MaxScale - 1.0f) * ElasticValue; // 마지막 크기 ( 1.5 - (0.5* 수식))
		Animal->SetActorScale3D(FVector(ScaleFactor, ScaleFactor, ScaleFactor));
		UE_LOG(LogTemp, Log, TEXT("Scaling %s: t=%f, Scale=%f"), *Animal->GetName(), t, ScaleFactor);

		if (t >= 1.0f)
		{
			bIsScaling = false;
			ScaleTime = 0.0f;
			Animal->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
			UE_LOG(LogTemp, Log, TEXT("Scale finished for %s"), *Animal->GetName());
		
		}
	}
}

void USBS_AnimalFSM::Stay(float Deltatime)
{
	if(GameMode->Phase2)
	{
		CurrentTime += Deltatime;
		if(CurrentTime > 3)
		{
		}
	}
	SetState(ESBS_AnimalState::Idle);
	AnimalAnim->bMoving = false;
	AnimalAnim->bGrab = false;
}

void USBS_AnimalFSM::IdleState()
{
	//Animal->BoxComp->SetSimulatePhysics(true);
	Animal->SkeletalMesh->SetVisibility(true);
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime >= StayTime)
	{
		CurrentTime = 0;
		SetState(ESBS_AnimalState::Move);
	}
	if (AnimalAnim)
	{
		AnimalAnim->bMoving = false;
		AnimalAnim->bGrab = false;
	}
}

void USBS_AnimalFSM::MoveState()
{
	if (Animal)
	{
		FVector CurrentAnimalLocation = Animal->GetActorLocation();
		//Firepit = Cast<ASBS_FirePit>(UGameplayStatics::GetActorOfClass(GetWorld(), ASBS_FirePit::StaticClass()));
		//if (Firepit)
		//{
		//	AnimalDir = Firepit->GetActorLocation() - Animal->GetActorLocation();
		//	AnimalDir.Z = 0;
		//	AnimalDir.Normalize();
		//}
		//else
		//	AnimalDir = Animal-> GetActorForwardVector();
		if (LeaderAnimal && LeaderAnimal != Animal && LeaderAnimal->bInSafeZone)
		{
			AnimalDir = (LeaderAnimal->GetActorLocation() - CurrentAnimalLocation).GetSafeNormal();
			//AnimalDir.Z = 0;  // 수평 이동만
		}
		CurrentTime += GetWorld()->DeltaTimeSeconds;
		if (CurrentTime > 3)
		{
			ChangeDir(false);
			CurrentTime = 0;
		}
		FHitResult Hitresult;

		bool bMoved = Animal->SetActorLocation(CurrentAnimalLocation + AnimalDir*AnimalSpeed*GetWorld()->GetDeltaSeconds(), true, &Hitresult);

		const float MinpenetrationDepth = 5;
		// && Hitresult.PenetrationDepth>=MinpenetrationDepth
		//Hitresult.GetActor()->GetName().Contains(TEXT("Floor"))
		if (!bMoved && Hitresult.bBlockingHit && !(Hitresult.GetActor()->ActorHasTag(TEXT("Floor"))))
		{

			//UE_LOG(LogTemp, Log, TEXT("HitActor: %s"), *Hitresult.GetActor()->GetName());

			ChangeDir(true);
			Animal->SetActorScale3D(FVector(MaxScale, MaxScale, MaxScale));
			Animal->SetActorLocation(CurrentAnimalLocation + AnimalDir * AnimalSpeed * GetWorld()->GetDeltaSeconds(), true, &Hitresult);

		}

		Animal->SetActorRotation(FRotator(0, AnimalDir.Rotation().Yaw, 0));
	}
	if (AnimalAnim)
	{
	AnimalAnim->bMoving = true;
	AnimalAnim->bGrab = false;
	}
}

void USBS_AnimalFSM::InAir()
{
	//if (CurrentTime > StayTime)
	//{
	//	SetState(ESBS_AnimalState::Idle);
	//}
	if (AnimalAnim)
	{
	AnimalAnim->bMoving = false;
	AnimalAnim->bGrab = true;
	}
}

void USBS_AnimalFSM::Burning()
{
	AnimalHealth = Animal->Health;
	Firepit = Cast<ASBS_FirePit>(GetOwner());
	float CurrentTime2 = 0;
	if (CurrentTime2 > BurnTime)
	{
		AnimalHealth -= Firepit->FireDamage;
		CurrentTime2 = 0;
		if (AnimalHealth <= 0)
		{
			SetState(ESBS_AnimalState::Dead);
			GameMode->GameOver();
		}
	}
}

void USBS_AnimalFSM::Dead()
{
	
}

void USBS_AnimalFSM::ChangeDir(bool Crash)
{
	AnimalDir = (FVector(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f), 0)).GetSafeNormal();
	bCrash = false;
	if (Crash)
	{
		bIsScaling = true;
		ScaleTime = 0;
	}
}