// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyData.generated.h"

class UBehaviorTree;
class AEnemyBase;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_ELYDRIS_API UEnemyData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	//Clase del enemigo la cual se instanciara
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	TSubclassOf<AEnemyBase> EnemyClass;
	//Stats del enemigo
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float MoveSpeed = 300.f;

	//Animacion de muerte del enemigo
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
};
