// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/TextBlock.h"

void UHUDWidget::OnNotify(FName EventName, float NewValue)
{
	if (EventName == "HealthChanged" && HealthText)
	{
		HealthText->SetText(FText::FromString(FString::Printf(TEXT("HP: %.0f"), NewValue)));
	}
	else if (EventName == "Score Changed" && ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString(TEXT("Score: %d"), (int32)NewValue)));
	}
}
