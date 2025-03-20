// Fill out your copyright notice in the Description page of Project Settings.

#include "KJW/LaserRoom/Textboard.h"
#include "Components/TextBlock.h"

void UTextboard::SetTextBlock(FText text)
{
	Textboard->SetText(text);
}
