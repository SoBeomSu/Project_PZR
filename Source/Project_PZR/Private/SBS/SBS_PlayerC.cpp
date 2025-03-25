// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_PlayerC.h"
#include "Camera/CameraComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "SBS/SBS_PlayerFSM.h"
#include "SBS/SBS_Animal.h"
#include "SBS/SBS_AnimalFSM.h"
#include "SBS/SBS_LightSwitch.h"
#include "MotionControllerComponent.h"

// Sets default values
ASBS_PlayerC::ASBS_PlayerC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);
	playerFSM = CreateDefaultSubobject<USBS_PlayerFSM>(TEXT("FSMcomp"));

	LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(RootComponent);
	LeftHand->SetTrackingMotionSource(TEXT("Left"));
	RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(RootComponent);
	RightHand->SetTrackingMotionSource(TEXT("Right"));

	RightAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightAim"));
	RightAim->SetupAttachment(RootComponent);
	RightAim->SetTrackingMotionSource(TEXT("RightAim"));

}

// Called when the game starts or when spawned
void ASBS_PlayerC::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ASBS_GameMode>(GetWorld()->GetAuthGameMode());
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
		//InputSystem->BindAction(IA_MouseRightButton, ETriggerEvent::Started, this, &ASBS_PlayerC::RMB_Start);
		InputSystem->BindAction(IA_MouseRightButton, ETriggerEvent::Started, this, &ASBS_PlayerC::GrabStart);
		InputSystem->BindAction(IA_MouseRightButton, ETriggerEvent::Completed, this, &ASBS_PlayerC::GrabEnd);

		InputSystem->BindAction(IA_MouseLeftButton, ETriggerEvent::Started, this, &ASBS_PlayerC::LRB_Start);
		InputSystem->BindAction(IA_MouseLeftButton, ETriggerEvent::Completed, this, &ASBS_PlayerC::LRB_Complete);
	}
}

void ASBS_PlayerC::GrabStart()
{
	if (!VRCamera) return;
	//이미 잡은 물체가 있다면
	if (GrabObj) return;

	// 카메라의 위치와 방향 가져오기
	FVector StartLocation = VRCamera->GetComponentLocation();
	FVector EndLocation = StartLocation + VRCamera->GetForwardVector() * 100.0f;

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
			if (GrabbableObject && GrabbableObject->IsGrab())
			{
				// 그랩 로직 (이 인터페이스를 통해 실제 그랩 기능 호출)
				GrabbableObject->StartGrab(RightHand, true);
				GrabObj = GrabbableObject;
			}
		}
	}

}

void ASBS_PlayerC::GrabEnd()
{
	if (!GrabObj) return;

	GrabObj->StopGrab(RightHand, true);
	GrabObj = nullptr;
}

void ASBS_PlayerC::Move(const struct FInputActionValue& Value)
{
	FVector2d Scale = Value.Get<FVector2d>();
	FVector Direction = VRCamera->GetForwardVector() * Scale.X + VRCamera->GetRightVector() * Scale.Y;
	AddMovementInput(Direction, MoveSpeedVal); // 이렇게 한번에 해주는게 좋다.
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
		FHitResult RMB_HitResult = CameraLineTrace(); // 라인트레이스를 쏜다
		AActor* HitActor = RMB_HitResult.GetActor();
		if (HitActor)
		{
			if (HitActor->GetActorNameOrLabel().Contains("Animal")) // 잡은게 애니멀이면
			{
				ASBS_Animal* HitAnimal = Cast<ASBS_Animal>(RMB_HitResult.GetActor());
				if (HitAnimal && HitAnimal->AnimalFSM) 
				{
					HitAnimal->AnimalFSM->SetState(ESBS_AnimalState::InAir);
					AttachActor(HitAnimal);
				}
			}
			if (HitActor->GetActorNameOrLabel().Contains("Switch")) // 잡은게 스위치면
			{
				MoveSpeedVal = 0;
				LightSwitch = Cast<ASBS_LightSwitch>(RMB_HitResult.GetActor());
				if (LightSwitch && LightSwitch->bCanGrap)
				{
					LightSwitch->SetSwitchRotation(90);
					GrabActor = LightSwitch;
					UE_LOG(LogTemp, Warning, TEXT("Light Work"));

				}
			}
			if (HitActor->GetActorNameOrLabel().Contains("Button")) // 버튼이면
			{
				StartButton = Cast<ASBS_GameStartButton>(RMB_HitResult.GetActor());\
				if (StartButton)
				{
					StartButton->ButtonPressed();
				}
			}
		}
	} 
}

void ASBS_PlayerC::RMB_Complete(const struct FInputActionValue& Value)
{
	if (GrabActor)
	{
		ASBS_Animal* HitAnimal = Cast<ASBS_Animal>(GrabActor);
		if (HitAnimal)
		{
			HitAnimal->AnimalFSM->SetState(ESBS_AnimalState::Idle);
			DetachActor(GrabActor);
		}
		//LightSwitch = Cast<ASBS_LightSwitch>(GrabActor);
		if (GrabActor == LightSwitch && GameMode->bStartGame)
		{
			LightSwitch->StartReset();
		//	GrabActor = nullptr;
		}
	}
	MoveSpeedVal = 1;
	bRightclick = false;
}

void ASBS_PlayerC::LRB_Start(const struct FInputActionValue& Value)
{
	bLeftclick = true;
}

void ASBS_PlayerC::LRB_Complete(const struct FInputActionValue& Value)
{
	bLeftclick = false;
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
	UE_LOG(LogTemp, Warning, TEXT("Attach"));
}

void ASBS_PlayerC::DetachActor(AActor* actor)
{
	actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	GrabActor = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("Detach"));
}

