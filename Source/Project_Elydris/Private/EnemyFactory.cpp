// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFactory.h"
#include  "EnemyData.h"
#include  "EnemyBase.h"
#include "Engine/World.h"

TSubclassOf<AEnemyBase> AEnemyFactory::ResolveClass(const UEnemyData* Data) const
{
	return Data ? Data->EnemyClass : nullptr;
}


AEnemyBase* AEnemyFactory::SpawnEnemy_Implementation(const UEnemyData* Data, const FEnemySpawnContext& Ctx)
{
	if (!Data) return nullptr;


	TSubclassOf<AEnemyBase> ClassToSpawn = ResolveClass(Data);
	if (!*ClassToSpawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyFactory: EnemyClass nulo en DataAsset"));
		return nullptr;
	}


	FActorSpawnParameters Params;
	Params.Owner = Ctx.Owner.Get();
	Params.Instigator = Ctx.Instigator.Get();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	return GetWorld()->SpawnActor<AEnemyBase>(Data->EnemyClass, Ctx.Transform, Params);
	
	
}
