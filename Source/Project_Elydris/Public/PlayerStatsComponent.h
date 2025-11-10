// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IObserver.h"
#include "PlayerStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_ELYDRIS_API UPlayerStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Score = 0;
	void AddObserver(TScriptInterface<IObserver>Metiche);
	void RemoveObserver(TScriptInterface<IObserver>Metiche);
	void SetHealth(float NewHealth);
	void AddScore(int32 Points);
private:
	UPROPERTY()
	TArray<TScriptInterface<IObserver>> Observers;

	void Notify(FName EventName, float Value);

		
};
