// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "Command.h"
#include "CommandInvoker.h"
#include "CommandPlayer.generated.h"

// Declaración de delegados
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDashEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMoveEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnstopMoveEvent);

UCLASS()
class PROJECT_ELYDRIS_API ACommandPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACommandPlayer();
	

	// Invoker y comandos
	UPROPERTY(Instanced, VisibleAnywhere, Category = "Command", BlueprintReadWrite)
	TObjectPtr<UCommandInvoker> CommandInvoker;

	UPROPERTY(Instanced, VisibleAnywhere, Category = "Command", BlueprintReadWrite)
	TObjectPtr<UJumpCommand> JumpCommand;

	// Delegados utilizables en BP (AnimBP, etc.)
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnJumpEvent OnJumpEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnMoveEvent OnMoveEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnstopMoveEvent OnStopMoveEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDashEvent OnDashEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAttackEvent OnAttackEvent;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sobrecarga de SetupPlayerInputComponent, para bindear los Input Action
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Dirección de mirada del personaje (true = derecha, false = izquierda)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	bool bFacingRight = true;


private:
	// Referencias a InputMappingContext y los Input Actions
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* UndoAction;

	// NUEVOS: acciones de Dash y Attack
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* DashAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* AttackAction;

	// Funciones para encapsular los inputs posibles
	void OnJump(const FInputActionValue& Value);
	void OnMove(const FInputActionValue& Value);
	void OnStop(const FInputActionValue& Value);
	void OnUndo(const FInputActionValue& Value);

	// NUEVOS: callbacks de dash y ataque
	void OnDash(const FInputActionValue& Value);
	void OnAttack(const FInputActionValue& Value);
};
