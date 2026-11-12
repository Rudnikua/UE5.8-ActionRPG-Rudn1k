// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/MainOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMainOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar) HealthProgressBar->SetPercent(Percent);
}

void UMainOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar) StaminaProgressBar->SetPercent(Percent);
}

void UMainOverlay::SetGold(int32 Gold)
{
	// convert int32 to string to text
	if (GoldText) GoldText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Gold)));
}

void UMainOverlay::SetSouls(int32 Souls)
{
	// convert int32 to string to text
	if (SoulsText) SoulsText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Souls)));
}
