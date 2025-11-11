// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyData.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class UEnemyData;

UCLASS(Abstract, Blueprintable)
class PROJECT_ELYDRIS_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void InitializeFromData(const UEnemyData* Data);

	UFUNCTION(BlueprintPure, Category = "Enemy")
	FORCEINLINE float GetMaxHealth() const {return MaxHealth; }

protected:
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Stats")
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Stats")
	float MoveSpeed = 300.f;


};
