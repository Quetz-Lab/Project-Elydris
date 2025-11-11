#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"

AEnemyAIController::AEnemyAIController()
{
	// PawnControlRotation off for AI by default; no tick needed
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ThinkTimer, this, &AEnemyAIController::TickSeekTarget, RepathInterval, true);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyAIController::TickSeekTarget()
{
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player || !GetPawn()) return;

	MoveToActor(Player, AcceptanceRadius, true, true, true, 0, true);
}
