// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_LightSwitch.h"
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "SBS/SBS_WorldLightManager.h"

// Sets default values
ASBS_LightSwitch::ASBS_LightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch"));
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("PointLight"));

	SwitchMesh->SetupAttachment(RootComponent);
	SwitchMesh->SetMobility(EComponentMobility::Movable);
	SpotLight->SetupAttachment(RootComponent);
	SpotLight->SetVisibility(false);
}

// Called when the game starts or when spawned
void ASBS_LightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBS_LightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float SwitchXRot = GetActorRotation().Roll;
	if (SwitchXRot < 50)
	{
		bCanGrap = true;
	}
	if (FMath::IsNearlyEqual(SwitchXRot, 90, 1))
	{
		SwitchOn();
		if (bIsOn)
		{
			CurrentTime += DeltaTime;
			if (CurrentTime >= SwitchOffTime)
			{
				ResetRotation(DeltaTime);
			}
		}
	}
	else
	{
		ResetRotation(DeltaTime);
	}
}

void ASBS_LightSwitch::SetSwitchRotation(float SwitchRotate)
{
	this->SetActorRotation(FRotator(0, 0, SwitchRotate));
}


void ASBS_LightSwitch::StartReset()
{
	bIsResetting = true;
	//ResetTime = 0;
	StartAngle = this->GetActorRotation().Roll;
	UE_LOG(LogTemp, Log, TEXT("StarAngle: %f"), StartAngle);
}

void ASBS_LightSwitch::ResetRotation(float Deltatime)
{
	if (bIsResetting)
	{
		ResetTime += Deltatime;
		float LerpAlpha = ResetTime/ResetDuration;
		float NewAngle = FMath::Lerp(StartAngle, 0, LerpAlpha);
		this->SetActorRotation(FRotator(0,0,NewAngle));
		if (ResetTime >= ResetDuration)
		{
			bIsResetting = false;
			CurrentTime = 0;
			this->SetActorRotation(FRotator(0, 0, 0));
			SwitchOff();
		}
	}
	else if (CurrentTime >= SwitchOffTime && bIsOn)
	{
		bIsResetting = true;
		ResetTime = 0.0f;
		StartAngle = this->GetActorRotation().Roll;
	}
}

void ASBS_LightSwitch::SwitchOn()
{
	//불을 키는 작동
	this->SetActorRotation(FRotator(0,0,90));
	bIsOn =true;
	bCanGrap = false;
	SpotLight->SetVisibility(false);
	//WorldLight = Cast<ASBS_WorldLightManager>(GetOwner());
	if (WorldLight)
	{
		WorldLight->SpotLight->SetVisibility(true);
	}

}
void ASBS_LightSwitch::SwitchOff()
{
	//불끄기
	bIsOn = false;
	SpotLight->SetVisibility(true);
	//WorldLight = Cast<ASBS_WorldLightManager>(GetOwner());
	if (WorldLight)
	{
		WorldLight->SpotLight->SetVisibility(false);
	}
}

