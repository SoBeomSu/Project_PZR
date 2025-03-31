// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_Bomb.h"
#include "SBS/SBS_GameMode.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SBS/SBS_Animal.h"
#include "MotionControllerComponent.h"

// Sets default values
ASBS_Bomb::ASBS_Bomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Boxcollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollsion"));
	RootComponent = Boxcollision;
	//Boxcollision->SetSimulatePhysics(true);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Boxcollision);



	for (int i= 0; i <= 9; i++)
	{
		FString Name = FString::Printf(TEXT("Number%d"), i);
		UBoxComponent* NumPad = CreateDefaultSubobject<UBoxComponent>(*Name); //Number1 Number2
		NumPad->SetupAttachment(StaticMesh);
		NumPad->SetCollisionProfileName(TEXT("BlockAllDynamic")); // 충돌 설정
		NumPad->ComponentTags.Add(FName(*FString::FromInt(i))); // 태그로 숫자 지정
		NumberCollisions.Add(NumPad);
	}
	EnterKey = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterKey"));
	EnterKey->SetupAttachment(StaticMesh);
	EnterKey->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	DeleteKey = CreateDefaultSubobject<UBoxComponent>(TEXT("DeleteKey"));
	DeleteKey->SetupAttachment(StaticMesh);
	DeleteKey->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	PasswordWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PasswordWidget"));
	PasswordWidget->SetupAttachment(StaticMesh);
	TimeLeftWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TimeLeftWidget"));
	TimeLeftWidget->SetupAttachment(StaticMesh);


	
}

// Called when the game starts or when spawned
void ASBS_Bomb::BeginPlay()
{
	Super::BeginPlay();
	SetupKeypad();
	GameMode = Cast<ASBS_GameMode>(GetWorld()->GetAuthGameMode());
	TArray<AActor*> AnimalArr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASBS_Animal::StaticClass(), AnimalArr);

	//if (AnimalArr.Num() != 0)
	//{
	//	int randomindex = FMath::RandRange(0, AnimalArr.Num()-1);
	//	auto RandomAnimal = AnimalArr[randomindex];
	//	if (RandomAnimal)
	//	{
	//		AttachToActor(RandomAnimal, FAttachmentTransformRules::KeepWorldTransform);
	//
	//		FVector Offset = RandomAnimal->GetActorForwardVector()* -50 + FVector(0,0,50);
	//		SetActorLocation(RandomAnimal->GetActorLocation() + Offset);
	//	}
	//}
}

// Called every frame
void ASBS_Bomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASBS_Bomb::SetupKeypad()
{

}

void ASBS_Bomb::OnButtonPressed(FHitResult& HitResult, EVRButton VRButton)
{

	UBoxComponent* HitBox = Cast<UBoxComponent>(HitResult.GetComponent());
	if (HitBox)
	{
		UE_LOG(LogTemp, Log, TEXT("***@@*@*@**@"));
	}
	if (HitBox && HitBox == EnterKey)
	{
		PressEnter();
	}
	if (HitBox && HitBox == DeleteKey)
	{
		PressDelete();
	}
	if (HitBox && NumberCollisions.Contains(HitBox) && Password.Len() <4)
	{
		FName Tag = HitBox->ComponentTags[0];
		int Number = FCString::Atoi(*Tag.ToString());
		Password.AppendInt(Number); // 정수를 문자열로 변환헤 fstring에 추가
		UpdateWidgetText();
	}
}

void ASBS_Bomb::StartGrab(class UMotionControllerComponent* MontionComp, bool IsRight)
{
	Boxcollision->SetSimulatePhysics(false);
	this->AttachToComponent(MontionComp, FAttachmentTransformRules::KeepWorldTransform);

	UE_LOG(LogTemp, Warning, TEXT("Bomb Grab"));
}

void ASBS_Bomb::StopGrab(class UMotionControllerComponent* MontionComp, bool IsRight)
{
	Boxcollision->SetSimulatePhysics(true);
	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	UE_LOG(LogTemp, Warning, TEXT("Bomb Release"));
}

FString ASBS_Bomb::WritePassword(int Numbers)
{

	return Password;
}

void ASBS_Bomb::PressEnter()
{
	if (Password == Answer)
	{
		bCorrect= true;
		GameMode->SetPasswordCorrect(bCorrect);
	}
	else
	{
		
	}
}

void ASBS_Bomb::PressDelete()
{
	if (!Password.IsEmpty())
	{
		Password = Password.LeftChop(1);
		UpdateWidgetText();
	}
}

void ASBS_Bomb::UpdateWidgetText()
{
	UE_LOG(LogTemp, Log, TEXT("Current Password: %s"), *Password);
}

void ASBS_Bomb::UpdateBombMaterial(int CorrectCount)
{
	switch(CorrectCount)
	{
		case 1:
			if (OneGreen)
			StaticMesh->SetMaterial(0, OneGreen);
			break;
		case 2:
			if (TwoGreen)
			StaticMesh->SetMaterial(0, TwoGreen);
			break;
		case 3:
			if(ThreeGreen)
			StaticMesh->SetMaterial(0, ThreeGreen);
			break;
		default:
			break;

	}
	UE_LOG(LogTemp, Log, TEXT("Bomb Update"));
}

