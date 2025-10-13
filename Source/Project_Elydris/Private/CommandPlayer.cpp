// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandPlayer.h"

// Sets default values
ACommandPlayer::ACommandPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACommandPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACommandPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACommandPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

