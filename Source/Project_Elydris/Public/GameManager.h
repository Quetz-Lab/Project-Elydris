
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OptionsModel.h"
#include "OptionsController.h"
#include "GameManager.generated.h"

UCLASS()
class PROJECT_ELYDRIS_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	// Acceso global desde BP: GetGameInstance → cast a UGameManager
	UFUNCTION(BlueprintPure, Category="Managers")
	UOptionsModel* GetOptionsModel() const { return OptionsModel; }

	UFUNCTION(BlueprintPure, Category="Managers")
	UOptionsController* GetOptionsController() const { return OptionsController; }

protected:
	virtual void Init() override;

private:
	UPROPERTY()
	UOptionsModel* OptionsModel = nullptr;

	UPROPERTY()
	UOptionsController* OptionsController = nullptr;
};
