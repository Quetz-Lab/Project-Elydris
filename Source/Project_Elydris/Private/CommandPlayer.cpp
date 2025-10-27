// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandPlayer.h"
#include "Command.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "PlayerStatsComponent.h"
#include "HUDWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACommandPlayer::ACommandPlayer()
{
    //creacin del invoker
    CommandInvoker = CreateDefaultSubobject<UCommandInvoker>(TEXT("CommandInvoker"));

    //creacin del JumpCommand
    JumpCommand = CreateDefaultSubobject<UJumpCommand>(TEXT("JumpCommand"));
    JumpCommand->SetCharacter(this);
    InputMappingContext = nullptr;

    /*UE_LOG(LogTemp, Log, TEXT("ACommandCharacter::Constructor, CommandInvoker: %s, JumpCommand: %s"),
        *GetNameSafe(CommandInvoker), *GetNameSafe(JumpCommand));*/
}

void ACommandPlayer::BeginPlay()
{
    Super::BeginPlay();

  
    // Reinicializar CommandInvoker y JumpCommand si son nulos.
    if (!CommandInvoker)
    {
        CommandInvoker = NewObject<UCommandInvoker>(this, TEXT("CommandInvoker"));
        UE_LOG(LogTemp, Warning, TEXT("CommandInvoker was null, reinitialized in BeginPlay"));
    }
    if (!JumpCommand)
    {
        JumpCommand = NewObject<UJumpCommand>(this, TEXT("JumpCommand"));
        JumpCommand->SetCharacter(this);
        UE_LOG(LogTemp, Warning, TEXT("JumpCommand was null, reinitialized in BeginPlay"));
    }

    UE_LOG(LogTemp, Log, TEXT("BeginPlay: CommandInvoker: %s, JumpCommand: %s"),
        *GetNameSafe(CommandInvoker), *GetNameSafe(JumpCommand));

    // Asegurar que el Personaje este en el piso
    if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
    {
        MovementComponent->SetMovementMode(MOVE_Walking);

        FHitResult Hit;
        FVector Start = GetActorLocation();
        FVector End = Start - FVector(0, 0, 50.0f);
        if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
        {
            SetActorLocation(Hit.Location + FVector(0, 0, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
            UE_LOG(LogTemp, Log, TEXT("Snapped character to ground at %s"), *Hit.Location.ToString());
        }
        if (bIsCrouched)
        {
            UnCrouch();
            UE_LOG(LogTemp, Log, TEXT("UnCrouched character"));
        }
        UE_LOG(LogTemp, Log, TEXT("BeginPlay: Set MovementMode to MOVE_Walking"));
    }

    if (InputMappingContext)
    {
        if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
            {
                Subsystem->AddMappingContext(InputMappingContext, 0);
                UE_LOG(LogTemp, Log, TEXT("Input Mapping Context applied: %s"), *GetNameSafe(InputMappingContext));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("EnhancedInputLocalPlayerSubsystem not found"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("PlayerController not found"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("InputMappingContext is null"));
    }
}

void ACommandPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UE_LOG(LogTemp, Log, TEXT("SetupPlayerInputComponent called, CommandInvoker: %s, JumpCommand: %s"),
        *GetNameSafe(CommandInvoker), *GetNameSafe(JumpCommand));

    //Bindear los Input Action del jugador
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (JumpAction)
        {
            UE_LOG(LogTemp, Log, TEXT("Binding JumpAction"));
            EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACommandPlayer::OnJump);
        }

        if (MoveAction)
        {
            UE_LOG(LogTemp, Log, TEXT("Binding MoveAction"));
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACommandPlayer::OnMove);

            //Crear dos Binds adicionales para el input de movimiento, completed y cancelled. Esto para llamar al evento OnStop cuando el jugador deje de moverse
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACommandPlayer::OnStop);
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &ACommandPlayer::OnStop);
        }                                                                                           
                                                                                                    
        if (UndoAction)                                                                             
        {                                                                                           
            UE_LOG(LogTemp, Log, TEXT("Binding UndoAction"));                                       
            EnhancedInputComponent->BindAction(UndoAction, ETriggerEvent::Triggered, this, &ACommandPlayer::OnUndo);
        }

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("EnhancedInputComponent cast failed"));
    }
}

void ACommandPlayer::OnJump(const FInputActionValue& Value)
{
    if (CommandInvoker && JumpCommand)
    {
        UE_LOG(LogTemp, Log, TEXT("Executing JumpCommand"));
        CommandInvoker->ExecuteCommand(JumpCommand);

        OnJumpEvent.Broadcast();
    }
}

void ACommandPlayer::OnMove(const FInputActionValue& Value)
{
    if (CommandInvoker)
    {
        FVector2D MovementInput = Value.Get<FVector2D>();

        if (MovementInput.IsNearlyZero())
        {
            UE_LOG(LogTemp, Log, TEXT("NotMoving"));
            OnStopMoveEvent.Broadcast();
            return;
        }

        FVector Forward = GetActorForwardVector();
        FVector Right = GetActorRightVector();
        FVector MoveDirection = (Forward * MovementInput.Y + Right * MovementInput.X).GetSafeNormal();

        //crear comando
        UCommandMove* MoveCommand = NewObject<UCommandMove>(this, UCommandMove::StaticClass());

        if (MovementInput.SquaredLength() > 0)
        {
            OnMoveEvent.Broadcast();
        }
        else
        {
            OnStopMoveEvent.Broadcast();
        }

        //Setear y ejecutar comando
        MoveCommand->SetCharacterAndInput(this, MoveDirection, MovementInput.Size());
        CommandInvoker->ExecuteCommand(MoveCommand);


        UE_LOG(LogTemp, Log, TEXT("ExecuteCommand(MoveCommand)"));
    }
}

void ACommandPlayer::OnStop(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Log, TEXT("OnStop called"));
    OnStopMoveEvent.Broadcast();
}



void ACommandPlayer::OnUndo(const FInputActionValue& Value)
{
    if (CommandInvoker)
    {
        UE_LOG(LogTemp, Log, TEXT("Executing Undo"));
        CommandInvoker->Undo();
    }
}

