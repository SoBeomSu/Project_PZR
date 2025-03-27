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

	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(RightHand);
	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	LeftHandMesh->SetupAttachment(LeftHand);




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
		//InputSystem->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASBS_PlayerC::Move);
		InputSystem->BindAction(IA_Thumb_L, ETriggerEvent::Triggered, this, &ASBS_PlayerC::Move);
		InputSystem->BindAction(IA_Thumb_R, ETriggerEvent::Triggered, this, &ASBS_PlayerC::Thumb_RInput);

		InputSystem->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ASBS_PlayerC::Turn);
		
		InputSystem->BindAction(IA_R_Grip_Click, ETriggerEvent::Started, this, &ASBS_PlayerC::GrabStart_R); // 마우스 우클릭 + 오른쪽 트리거
		InputSystem->BindAction(IA_R_Grip_Click, ETriggerEvent::Completed, this, &ASBS_PlayerC::GrabEnd_R);

		InputSystem->BindAction(IA_L_Grip_Click, ETriggerEvent::Started, this, &ASBS_PlayerC::GrabStart_L); //마우스 왼클릭 + 왼쪽 트리거
		InputSystem->BindAction(IA_L_Grip_Click, ETriggerEvent::Completed, this, &ASBS_PlayerC::GrabEnd_L);

		InputSystem->BindAction(IA_Button_A, ETriggerEvent::Started, this, &ASBS_PlayerC::ButtonPressed_A); // A 버튼
		InputSystem->BindAction(IA_Button_A, ETriggerEvent::Completed, this, &ASBS_PlayerC::ButtonReleased); // 

		InputSystem->BindAction(IA_Button_X, ETriggerEvent::Started, this, &ASBS_PlayerC::ButtonPressed_X); // X 버튼
		InputSystem->BindAction(IA_Button_X, ETriggerEvent::Completed, this, &ASBS_PlayerC::ButtonReleased); //
	}
}

void ASBS_PlayerC::GrabStart_R()
{
	UE_LOG(LogTemp, Warning, TEXT("click success"));
	if (!VRCamera) return;
	//이미 잡은 물체가 있다면
	if (GrabObj) return;

	// 카메라의 위치와 방향 가져오기
	FVector StartLocation = VRCamera->GetComponentLocation();
	FVector EndLocation = StartLocation + VRCamera->GetForwardVector() * 100.0f;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 자기 자신 무시
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_GameTraceChannel1, QueryParams);
	
	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trae Hit"));

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
				UE_LOG(LogTemp, Warning, TEXT("grab sucess"));
			}
		}
	}

}

void ASBS_PlayerC::GrabEnd_R()
{
	if (!GrabObj) return;

	GrabObj->StopGrab(RightHand, true);
	GrabObj = nullptr;
}

void ASBS_PlayerC::GrabStart_L()
{

}

void ASBS_PlayerC::GrabEnd_L()
{

}

void ASBS_PlayerC::ButtonPressed_A()
{
	ButtonPressed(EVRButton::Right_A_Button);
}

void ASBS_PlayerC::ButtonPressed_X()
{
	ButtonPressed(EVRButton::Left_X_Button);
}

void ASBS_PlayerC::ButtonPressed(EVRButton VRButton)
{
	UE_LOG(LogTemp, Warning, TEXT("click success"));
	if (!VRCamera) return;

	// 카메라의 위치와 방향 가져오기
	FVector StartLocation = VRCamera->GetComponentLocation();
	FVector EndLocation = StartLocation + VRCamera->GetForwardVector() * 100.0f;

	FHitResult HitResult;
	if(GrabObj) GrabObj->OnButtonPressed(HitResult, VRButton);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 자기 자신 무시

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);

	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trae Hit"));

		AActor* HitActor = HitResult.GetActor();
		//UPrimitiveComponent* HitComponent = HitResult.GetComponent();

		if (HitActor)
		{
			// IKVRObjectInterface를 가진 오브젝트와 상호작용 시작
			IKVRObjectInterface* GrabbableObject = Cast<IKVRObjectInterface>(HitActor);
			if (GrabbableObject)
			{
				// 그랩 로직 (이 인터페이스를 통해 실제 그랩 기능 호출)
				GrabbableObject->OnButtonPressed(HitResult, VRButton);
				UE_LOG(LogTemp, Warning, TEXT("Button Pressed"));
			}
		}
	}
}


void ASBS_PlayerC::ButtonReleased()
{

}

void ASBS_PlayerC::Move(const struct FInputActionValue& Value)
{

	FVector2d Scale = Value.Get<FVector2d>();
	UE_LOG(LogTemp, Warning, TEXT("%f , %f"), Scale.X, Scale.Y);
	FVector Direction = VRCamera->GetForwardVector() * Scale.X + VRCamera->GetRightVector() * Scale.Y;
	AddMovementInput(Direction, MoveSpeedVal); // 이렇게 한번에 해주는게 좋다.
}

void ASBS_PlayerC::Thumb_RInput(const FInputActionValue& Value)
{
	FVector2d Scale = Value.Get<FVector2d>();
	if (GrabObj)
	{
		GrabObj->OnThumbstickValue(RightHand, true, Scale);
	}
}

void ASBS_PlayerC::Turn(const struct FInputActionValue& Value)
{
	FVector2d Scale = Value.Get<FVector2d>();
	AddControllerYawInput(Scale.X); // 좌우
	AddControllerPitchInput(Scale.Y); // 위아래
}

FHitResult ASBS_PlayerC::CameraLineTraceHitResult()
{
	FVector StartLocation = VRCamera->GetComponentLocation();
	FVector EndLocation = StartLocation + VRCamera->GetForwardVector() * 100.0f;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 자기 자신 무시
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_GameTraceChannel1, QueryParams);
	return HitResult;
}

void ASBS_PlayerC::AttachActor(AActor* actor)
{
	actor->AttachToActor(this,FAttachmentTransformRules::KeepWorldTransform);
	GrabActor = actor;
	UE_LOG(LogTemp, Warning, TEXT("Attach"));
}

