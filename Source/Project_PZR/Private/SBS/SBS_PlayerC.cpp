// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_PlayerC.h"
#include "Camera/CameraComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "SBS/SBS_PlayerFSM.h"
#include "SBS/SBS_Animal.h"
#include "SBS/SBS_AnimalFSM.h"

// Sets default values
ASBS_PlayerC::ASBS_PlayerC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);

	playerFSM = CreateDefaultSubobject<USBS_PlayerFSM>(TEXT("FSMcomp"));
}

// Called when the game starts or when spawned
void ASBS_PlayerC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBS_PlayerC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASBS_PlayerC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc)
	{
		auto LocalPlayer = pc->GetLocalPlayer();
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
		if (subsystem)
		{
			subsystem->AddMappingContext(IMC_VR, 1); // 우선도 1
		}
	}
	auto InputSystem = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputSystem)
	{
		InputSystem->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASBS_PlayerC::Move);
		InputSystem->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ASBS_PlayerC::Turn);
		InputSystem->BindAction(IA_MouseRightButton, ETriggerEvent::Started, this, &ASBS_PlayerC::RMB_Start);
		InputSystem->BindAction(IA_MouseRightButton, ETriggerEvent::Completed, this, &ASBS_PlayerC::RMB_Complete);
		InputSystem->BindAction(IA_MouseLeftButton, ETriggerEvent::Started, this, &ASBS_PlayerC::LRB_Start);
		InputSystem->BindAction(IA_MouseLeftButton, ETriggerEvent::Completed, this, &ASBS_PlayerC::LRB_Complete);

	}
}

void ASBS_PlayerC::Move(const struct FInputActionValue& Value)
{
	FVector2d Scale = Value.Get<FVector2d>();
	FVector Direction = VRCamera->GetForwardVector() * Scale.X + VRCamera->GetRightVector() * Scale.Y;
	AddMovementInput(Direction); // 이렇게 한번에 해주는게 좋다.
}

void ASBS_PlayerC::Turn(const struct FInputActionValue& Value)
{
	FVector2d Scale = Value.Get<FVector2d>();
	AddControllerYawInput(Scale.X); // 좌우
	AddControllerPitchInput(Scale.Y); // 위아래
}

void ASBS_PlayerC::RMB_Start(const struct FInputActionValue& Value)
{
	if(bRightclick == false)
	{
		bRightclick = true;
		UE_LOG(LogTemp, Warning, TEXT("Right Click Sucess"));
		FHitResult RMB_HitResult = CameraLineTrace();
		if (RMB_HitResult.GetActor()->GetActorNameOrLabel().Contains("Animal"))
		{
			ASBS_Animal* HitAnimal = Cast<ASBS_Animal>(RMB_HitResult.GetActor());
			if (HitAnimal && HitAnimal->AnimalFSM) 
			{
				HitAnimal->AnimalFSM->SetState(ESBS_AnimalState::InAir);
				AttachActor(HitAnimal);
			}
		}
	}
	else
	{
		bRightclick = false;
	}
}

void ASBS_PlayerC::RMB_Complete(const struct FInputActionValue& Value)
{
	if (GrabActor)
	{
	DetachActor(GrabActor);
	}
}

void ASBS_PlayerC::LRB_Start(const struct FInputActionValue& Value)
{

}

void ASBS_PlayerC::LRB_Complete(const struct FInputActionValue& Value)
{

}

FHitResult ASBS_PlayerC::CameraLineTrace()
{
	FVector StartPoint = VRCamera->GetComponentLocation();
	FVector Endpoint = StartPoint + VRCamera->GetForwardVector() * 1000.0f;//10 미터
	FHitResult HitInfo;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartPoint, Endpoint, ECollisionChannel::ECC_Visibility, Params);

	if (bHit)
	{
		FString HitActorname = HitInfo.GetActor()->GetActorNameOrLabel();
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name : %s"), *HitInfo.GetActor()->GetActorNameOrLabel());
	}
	return HitInfo;
}

void ASBS_PlayerC::AttachActor(AActor* actor)
{
	actor->AttachToActor(this,FAttachmentTransformRules::KeepWorldTransform);
	GrabActor = actor;
}

void ASBS_PlayerC::DetachActor(AActor* actor)
{
	actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	GrabActor = nullptr;
}

