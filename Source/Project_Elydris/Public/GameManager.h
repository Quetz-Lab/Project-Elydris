
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OptionsModel.h"
#include "OptionsController.h"
#include  "Sound/SoundClass.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Audio")
	USoundClass* MasterSoundClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Audio")
	USoundClass* MusicSoundClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Audio")
	USoundClass* SFXSoundClass;

private:
	UPROPERTY()
	UOptionsModel* OptionsModel = nullptr;

	UPROPERTY()
	UOptionsController* OptionsController = nullptr;
};
