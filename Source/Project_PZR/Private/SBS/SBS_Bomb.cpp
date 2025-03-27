// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_Bomb.h"
#include "SBS/SBS_GameMode.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ASBS_Bomb::ASBS_Bomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	for (int i= 1; i <= 9; i++)
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
	if (HitBox && NumberCollisions.Contains(HitBox))
	{
		FName Tag = HitBox->ComponentTags[0];
		int Number = FCString::Atoi(*Tag.ToString());
		Password.AppendInt(Number); // 정수를 문자열로 변환헤 fstring에 추가
		UpdateWidgetText();
	}
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
		GameMode->InsertCorrectAnswer();
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

