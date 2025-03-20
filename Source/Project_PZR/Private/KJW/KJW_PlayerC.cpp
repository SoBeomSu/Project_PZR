// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/KJW_PlayerC.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

// Sets default values
AKJW_PlayerC::AKJW_PlayerC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCObj(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/A_Project/Input/IMC_VR.IMC_VR'"));
	if (IMCObj.Succeeded())
	{
		IMC_VR = IMCObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionObj(TEXT("/Script/EnhancedInput.InputAction'/Game/A_Project/Input/IA_VRMove.IA_VRMove'"));
	if (MoveActionObj.Succeeded())
	{
		IA_Move = MoveActionObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MouseActionObj(TEXT("/Script/EnhancedInput.InputAction'/Game/A_Project/Input/IA_VRTurn.IA_VRTurn'"));
	if (MouseActionObj.Succeeded())
	{
		IA_Mouse = MouseActionObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Mouse_LActionObj(TEXT("/Script/EnhancedInput.InputAction'/Game/A_Project/Input/IA_VRMouse_L.IA_VRMouse_L'"));
	if (Mouse_LActionObj.Succeeded())
	{
		IA_VRMouse_L = Mouse_LActionObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Mouse_RActionObj(TEXT("/Script/EnhancedInput.InputAction'/Game/A_Project/Input/IA_VRMouse_R.IA_VRMouse_R'"));
	if (Mouse_RActionObj.Succeeded())
	{
		IA_VRMouse_R = Mouse_RActionObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> KeyEActionObj(TEXT("/Script/EnhancedInput.InputAction'/Game/A_Project/KJW/IA_KeyE.IA_KeyE'"));
	if (KeyEActionObj.Succeeded())
	{
		IA_KeyE = KeyEActionObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> KeyQActionObj(TEXT("/Script/EnhancedInput.InputAction'/Game/A_Project/KJW/IA_KeyQ.IA_KeyQ'"));
	if (KeyQActionObj.Succeeded())
	{
		IA_KeyQ = KeyQActionObj.Object;
	}
}

// Called when the game starts or when spawned
void AKJW_PlayerC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKJW_PlayerC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKJW_PlayerC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!Controller) { return; }
	if (!IMC_VR) { return; }

	// DefaultMappingContext »ý¼º
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_VR, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		//if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(IA_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Turn);

	}
}

void AKJW_PlayerC::Move(const FInputActionValue& Value)
{
	FVector2D Scale = Value.Get<FVector2D>();
	Scale.Normalize();

	FVector Direction = VRCamera->GetForwardVector() * Scale.X
		+ VRCamera->GetRightVector() * Scale.Y;

	VRCamera->GetComponentTransform().TransformVector(Direction);
	AddMovementInput(Direction);
}

void AKJW_PlayerC::Turn(const FInputActionValue& Value)
{
	FVector2D Scale = Value.Get<FVector2D>();
	Scale.Normalize();

	AddControllerPitchInput(Scale.Y);
	AddControllerYawInput(Scale.X);
}

