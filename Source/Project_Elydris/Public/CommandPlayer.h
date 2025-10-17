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

//Declaracin de delegados
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
	UPROPERTY(Instanced, VisibleAnywhere, Category = "Command", BlueprintReadWrite)
	TObjectPtr<UCommandInvoker> CommandInvoker;
	UPROPERTY(Instanced, VisibleAnywhere, Category = "Command", BlueprintReadWrite)
	TObjectPtr<UJumpCommand> JumpCommand;

	//Crear las referencias de los delegados, usar el macro UPROPERTY(BlueprintAssignable) para que tambin sea utilizable en BPs.
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnJumpEvent OnJumpEvent;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnMoveEvent OnMoveEvent;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnstopMoveEvent OnStopMoveEvent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Indicar sobrecarga de SetupPlayerInputComponent, para bindear los Input Action
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Referenciar InputMappingContext y los Input Actions
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;


	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* UndoAction;


	//Funciones para encapsular los inputs posibles
	void OnJump(const FInputActionValue& Value);
	void OnMove(const FInputActionValue& Value);

	void OnStop(const FInputActionValue& Value);
	void OnUndo(const FInputActionValue& Value);


};
