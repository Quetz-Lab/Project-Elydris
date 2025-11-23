// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Command.generated.h"

// Command.h


UCLASS(Abstract, BlueprintType, Blueprintable)
class PROJECT_ELYDRIS_API UCommand : public UObject
{
	GENERATED_BODY()
public:
	virtual void Execute() PURE_VIRTUAL(UCommand::Execute, );
	virtual void Undo() { }
};

// ===================== MOVE =====================

UCLASS()
class PROJECT_ELYDRIS_API UCommandMove : public UCommand
{
	GENERATED_BODY()

public:
	UCommandMove()
		: Character(nullptr)
		, MoveDirection(FVector::ZeroVector)
		, Scale(0.f)
		, PreviousLocation(FVector::ZeroVector)
	{
	}

	void SetCharacterAndInput(ACharacter* InCharacter, const FVector& InMoveDirection, float InScale)
	{
		Character       = InCharacter;
		MoveDirection   = InMoveDirection;
		Scale           = InScale;
	}

	virtual void Execute() override
	{
		if (Character.IsValid())
		{
			PreviousLocation = Character->GetActorLocation();
			Character->AddMovementInput(MoveDirection, Scale);
		}
	}

	virtual void Undo() override
	{
		if (Character.IsValid())
		{
			Character->SetActorLocation(PreviousLocation);
		}
	}

private:
	TWeakObjectPtr<ACharacter> Character;
	FVector MoveDirection;
	float   Scale;
	FVector PreviousLocation;
};

// ===================== JUMP =====================

UCLASS()
class PROJECT_ELYDRIS_API UJumpCommand : public UCommand
{
	GENERATED_BODY()

public:
	UJumpCommand()
		: Character(nullptr)
	{
	}

	void SetCharacter(ACharacter* InCharacter)
	{
		Character = InCharacter;
	}

	virtual void Execute() override
	{
		if (Character.IsValid() && Character->CanJump())
		{
			Character->Jump();
		}
	}

	virtual void Undo() override
	{
		if (Character.IsValid())
		{
			Character->StopJumping();
		}
	}

private:
	TWeakObjectPtr<ACharacter> Character;
};

// ===================== DASH =====================

UCLASS()
class PROJECT_ELYDRIS_API UDashCommand : public UCommand
{
	GENERATED_BODY()

public:
	UDashCommand()
		: Character(nullptr)
		, DashDirection(FVector::ZeroVector)
		, DashStrength(1500.f)
	{
	}

	void SetCharacterAndDirection(ACharacter* InCharacter, const FVector& InDirection, float InStrength = 1500.f)
	{
		Character    = InCharacter;
		DashDirection = InDirection.GetSafeNormal();
		DashStrength  = InStrength;
	}

	virtual void Execute() override
	{
		if (!Character.IsValid())
			return;

		// Dash simple tipo Hollow Knight (luego tú lo refinas con state/anim)
		const FVector DashVelocity = DashDirection * DashStrength;
		Character->LaunchCharacter(DashVelocity, true, false);
	}

	virtual void Undo() override
	{
		// Si quisieras, aquí podrías restaurar velocidad, pero no es obligatorio
	}

private:
	TWeakObjectPtr<ACharacter> Character;
	FVector DashDirection;
	float   DashStrength;
};

// ===================== ATTACK =====================

UCLASS()
class PROJECT_ELYDRIS_API UAttackCommand : public UCommand
{
	GENERATED_BODY()

public:
	UAttackCommand()
		: Character(nullptr)
	{
	}

	void SetCharacter(ACharacter* InCharacter)
	{
		Character = InCharacter;
	}

	virtual void Execute() override
	{
		if (!Character.IsValid())
			return;

		// Aquí solo hacemos algo sencillo.
		// Lo "bonito" (animaciones / hitbox) lo disparas desde el Player via eventos.
		UE_LOG(LogTemp, Log, TEXT("UAttackCommand::Execute - Attack triggered"));
	}

	virtual void Undo() override
	{
		// Podrías cancelar ataque si quieres, pero no es obligatorio.
	}

private:
	TWeakObjectPtr<ACharacter> Character;
};