// Fill out your copyright notice in the Description page of Project Settings.


#include "KJW/KJW_PlayerC.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

#include "KJW/KVRObjectInterface.h"

// Sets default values
AKJW_PlayerC::AKJW_PlayerC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCObj(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/A_Project/KJW/IMC_VR_K.IMC_VR_K'"));
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

	// DefaultMappingContext 생성
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

		//물체 잡기
		EnhancedInputComponent->BindAction(IA_VRMouse_R, ETriggerEvent::Started, this, &ThisClass::GrabStart);
		EnhancedInputComponent->BindAction(IA_VRMouse_R, ETriggerEvent::Completed, this, &ThisClass::GrabEnd);
		//물체 회전
		EnhancedInputComponent->BindAction(IA_KeyQ, ETriggerEvent::Triggered, this, &ThisClass::LRotGrabObj);
		EnhancedInputComponent->BindAction(IA_KeyE, ETriggerEvent::Triggered, this, &ThisClass::RRotGrabObj);
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

void AKJW_PlayerC::GrabStart()
{
	if (!VRCamera) return;
	//이미 잡은 물체가 있다면
	if (GrabObj) return;

	// 카메라의 위치와 방향 가져오기
	FVector StartLocation = VRCamera->GetComponentLocation();
	FVector EndLocation = StartLocation + VRCamera->GetForwardVector() * 1000.0f;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 자기 자신 무시

	// 라인트레이스 실행
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_GameTraceChannel1, QueryParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// IKVRObjectInterface를 가진 오브젝트와 상호작용 시작
			IKVRObjectInterface* GrabbableObject = Cast<IKVRObjectInterface>(HitActor);
			if(GrabbableObject && GrabbableObject->IsGrab())
			{
				// 그랩 로직 (이 인터페이스를 통해 실제 그랩 기능 호출)
				GrabbableObject->StartGrab(this);
				GrabObj = GrabbableObject;
			}
		}
	}

}

void AKJW_PlayerC::GrabEnd()
{
	if (!GrabObj) return;

	GrabObj->StopGrab(this);
	GrabObj = nullptr;

}

void AKJW_PlayerC::LRotGrabObj()
{
	if (!GrabObj) return;

	FRotator AddLeftRot = FRotator(0.0f, -10.0f * 0.02f, 0.0f);
	GrabObj->RotObject(AddLeftRot);
}

void AKJW_PlayerC::RRotGrabObj()
{
	if (!GrabObj) return;
	FRotator AddRightRot = FRotator(0.0f, 10.0f * 0.02f, 0.0f);
	GrabObj->RotObject(AddRightRot);
}

