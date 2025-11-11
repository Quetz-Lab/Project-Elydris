#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class PROJECT_ELYDRIS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	FTimerHandle ThinkTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float RepathInterval = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float AcceptanceRadius = 150.f;

	UFUNCTION()
	void TickSeekTarget();
};
