// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ELYDRIS_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	//Acceso a la instancia del singleton
	UFUNCTION(BlueprintPure, Category = "Managers")
	UGameManager* GetGameManager();

protected:
	virtual void Init() override;

	private:
	UPROPERTY(Transient)
	UGameManager* GameManagerInstance;

	
};
