// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IObserver.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ELYDRIS_API UHUDWidget : public UUserWidget, public IObserver
{
	GENERATED_BODY()

public:

	virtual void OnNotify(FName EventName, float NewValue) override;
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* ScoreText;
	
};
