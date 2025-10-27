// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsComponent.h"

// Sets default values for this component's properties

void UPlayerStatsComponent::AddObserver(TScriptInterface<IObserver> Metiche)
{
	if (!Observers.Contains(Metiche))
		Observers.Add(Metiche);
}

void UPlayerStatsComponent::RemoveObserver(TScriptInterface<IObserver> Metiche)
{
	Observers.Remove(Metiche);
}

void UPlayerStatsComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, 100.0f);
	Notify("HealthChanged", Health);
}

void UPlayerStatsComponent::AddScore(int32 Points)
{
	Score += Points;
	Notify("Score Changed", Score);
}

void UPlayerStatsComponent::Notify(FName EventName, float Value)
{
	for (auto& Metiche : Observers)
	{
		if (Metiche)
		{
			Metiche->OnNotify(EventName, Value);
		}
	}
}
