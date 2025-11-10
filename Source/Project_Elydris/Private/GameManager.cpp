// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

UGameManager* UGameManager::GetGameManager()
{
	return GameManagerInstance;
}

void UGameManager::Init()
{
	Super::Init();	
	GameManagerInstance = NewObject<UGameManager>(this, UGameManager::StaticClass());
}
