// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_PlayerC.h"
#include "Camera/CameraComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "SBS/SBS_PlayerFSM.h"

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
		InputSystem->BindAction(IA_MouseRightButton, ETriggerEvent::Started, this, &ASBS_PlayerC::MouseRightButton);
		InputSystem->BindAction(IA_MouseRightButton, ETriggerEvent::Completed, this, &ASBS_PlayerC::MouseRightButton);
		InputSystem->BindAction(IA_MouseLeftButton, ETriggerEvent::Started, this, &ASBS_PlayerC::MouseLeftButton);
		InputSystem->BindAction(IA_MouseLeftButton, ETriggerEvent::Completed, this, &ASBS_PlayerC::MouseLeftButton);

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

void ASBS_PlayerC::MouseRightButton(const struct FInputActionValue& Value)
{
	if(bRightclick == false)
	{
		bRightclick = true;
		UE_LOG(LogTemp, Warning, TEXT("Right Click Sucess"));
		CameraLineTrace();

	}
	else
	{
		bRightclick = false;
	}
}

void ASBS_PlayerC::MouseLeftButton(const struct FInputActionValue& Value)
{

}

void ASBS_PlayerC::CameraLineTrace()
{
	FVector StartPoint = VRCamera->GetComponentLocation();
	FVector Endpoint = StartPoint + VRCamera->GetForwardVector() * 1000.0f;//10 미터
	FHitResult HitInfo;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, StartPoint, Endpoint, ECollisionChannel::ECC_Visibility, Params);

	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name : %s"), *HitInfo.GetActor()->GetActorNameOrLabel());
	}
	//if(bHit && (Hitinfo.getName()))

}

