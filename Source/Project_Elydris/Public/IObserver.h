// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IObserver.generated.h"

/**
 * 
 */
UINTERFACE (MinimalAPI)

class UObserver : public UInterface
{
	GENERATED_BODY()
};

class IObserver 
{
	GENERATED_BODY()
public: 
	
	virtual void OnNotify(FName EventName, float NewValue) = 0;
};
