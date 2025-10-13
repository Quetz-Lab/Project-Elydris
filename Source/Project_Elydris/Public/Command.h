// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Command.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class PROJECT_ELYDRIS_API UCommand : public UObject
{
	GENERATED_BODY()
public:
	//Funcion Execute, llama a las funciones encapsuladas
	UFUNCTION(BlueprintCallable, Category = "Command")
	virtual void Execute() PURE_VIRTUAL(UCommand::Execute, );
	//Funcion Undo, deshace las funciones encapsuladas
	UFUNCTION(BlueprintCallable, Category = "Command")
	virtual void Undo() PURE_VIRTUAL(UCommand::Undo, );
};
