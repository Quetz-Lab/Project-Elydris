// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "EnemyData.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyBase::InitializeFromData(const UEnemyData* Data)
{
	if (!Data) return;
	MaxHealth = Data->MaxHealth;
	MoveSpeed = Data->MoveSpeed;

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->MaxWalkSpeed = MoveSpeed;
	}
}


