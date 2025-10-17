// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Command.h"
#include "CommandInvoker.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_ELYDRIS_API UCommandInvoker : public UObject
{
	GENERATED_BODY()
public:
	UCommandInvoker();

	UFUNCTION(BlueprintCallable, Category = "Command")

	//Funcion para ejecutar un comando
	void ExecuteCommand(UCommand* Command);

	//Funcion para deshacer el ultimo comando ejecutado
	UFUNCTION(BlueprintCallable, Category = "Command")
	void Undo();

private:
	//TArray, una lista en la que se almacenan los comandos ejecutados
	TArray<TObjectPtr<UCommand>> CommandHistory;

	
};
