// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandInvoker.h"

UCommandInvoker::UCommandInvoker()
{
}
/**
 * @brief Llamar esta funcin para ejecutar un comando
 * @param Command el comando a ejecutar y guardar en la lista
 */
void UCommandInvoker::ExecuteCommand(UCommand* Command)
{
	if (Command)
	{
		Command->Execute();
		CommandHistory.Add(Command);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CommandInvoker::ExecuteCommand received null command"));
	}
}

void UCommandInvoker::Undo()
{
	if (CommandHistory.Num() > 0)
	{
		//La funcin pop toma en ltimo comando de la lista aaddido LIFO (LastInFirstOut) y lo elimina una vez referenciado
		UCommand* LastCommand = CommandHistory.Pop();
		//ejecuta la funcin Undo del comando
		LastCommand->Undo();
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("CommandInvoker::Undo called, but History is empty"));
	}
}


