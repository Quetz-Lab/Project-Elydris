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
UCLASS ()
class PROJECT_ELYDRIS_API UCommandMove : public UCommand
{

	GENERATED_BODY()
public:
	UCommandMove()
	{
		Character = nullptr;
		MoveDirection = FVector::ZeroVector;
		Scale = 0.0f;
		PreviousLocation = FVector::ZeroVector;
	}
	//Funcion para establecer el personaje, la direccion del movimiento
	void SetCharacterAndInput(ACharacter* InCharacter, const FVector& InMoveDirection, float InScale)
	{
		Character = InCharacter;
		MoveDirection = InMoveDirection;
		Scale = InScale;
	}

	//Implementacion de las funciones Execute y Undo
	virtual void Execute() override
	{
		if (Character.IsValid())
		{
			//Almacenar la posicion previa del personaje
			PreviousLocation = Character->GetActorLocation();

			//Mover el personaje en la direccion especificada
			Character->AddMovementInput(MoveDirection, Scale);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MoveCommand::Execute - Character is no longer valid"));
		}
	}
	virtual void Undo() override
	{
		if (Character.IsValid())
		{
			//Restaurar la posicion previa del personaje
			Character->SetActorLocation(PreviousLocation);
		}
	}
private:

	TWeakObjectPtr<ACharacter> Character;
	//Vector para almacenar la direccion del movimiento
	FVector MoveDirection;
	float Scale;
	//Vector para almacenar la posicion previa del personaje
	FVector PreviousLocation;
};
UCLASS()
class PROJECT_ELYDRIS_API UJumpCommand : public UCommand
{
	GENERATED_BODY()
public:
	UJumpCommand()
	{
		Character = nullptr;
	}
	//Funcin para especificar al personaje
	void SetCharacter(ACharacter* InCharacter)
	{
		Character = InCharacter;
	}
	// Sobrecarga Execute y Undo
	virtual void Execute() override
	{
		if (Character.IsValid())
		{
			//Obtener el componente CharacterMovementComponent
			UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
			if (MovementComponent)
			{
				bool bCanJump = Character->CanJump();
				if (bCanJump)
				{
					Character->Jump();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Jump failed due to CanJump() returning false"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("JumpCommand::MovementComponent is null"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("JumpCommand::Character is invalid"));
		}
	}
	/**
 * @brief Implementacin Undo
 */
	virtual void Undo() override
	{
		if (Character.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("JumpCommand::Undo called"));
			Character->StopJumping();
		}
	}
private:
	TWeakObjectPtr<ACharacter> Character;

};