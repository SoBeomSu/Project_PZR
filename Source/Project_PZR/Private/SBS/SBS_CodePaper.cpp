// Fill out your copyright notice in the Description page of Project Settings.


#include "SBS/SBS_CodePaper.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ASBS_CodePaper::ASBS_CodePaper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    TextDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextDisplay"));
    TextDisplay->SetupAttachment(Root);
    TextDisplay->SetRelativeLocation(FVector(0, 0, 0)); // Root에 붙임
    TextDisplay->SetText(FText::FromString(TEXT("Value: 42"))); // 초기값
    TextDisplay->SetHorizontalAlignment(EHTA_Center); // 가운데 정렬
    TextDisplay->SetTextRenderColor(FColor::White); // 흰색 텍스트
    TextDisplay->SetWorldSize(20.0f); // 텍스트 크기
}

// Called when the game starts or when spawned
void ASBS_CodePaper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBS_CodePaper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


    UpdateTextDisplay();
}
void ASBS_CodePaper::UpdateTextDisplay()
{
    if (TextDisplay)
    {
        FString DisplayString = FString::Printf(TEXT("Value: %d"), DisplayValue);
        TextDisplay->SetText(FText::FromString(DisplayString));
    }
}
