// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyData.h"
#include "UObject/NoExportTypes.h"
#include "EnemyFactory.generated.h"

class AEnemyBase;
class UEnemyData;

USTRUCT(BlueprintType)
struct FEnemySpawnContext
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform Transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<AActor> Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<APawn> Instigator;
};

UCLASS()
class PROJECT_ELYDRIS_API AEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintNativeEvent, Category = "Factory")
	AEnemyBase* SpawnEnemy(const UEnemyData* Data, const FEnemySpawnContext& ctx);

	UFUNCTION(BlueprintCallable, Category = "Factory")
	virtual AEnemyBase* SpawnEnemy_Implementation(const UEnemyData* Data, const FEnemySpawnContext& Ctx);

protected:
virtual TSubclassOf<AEnemyBase> ResolveClass(const UEnemyData* Data) const;

};
