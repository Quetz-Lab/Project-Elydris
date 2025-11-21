#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OptionsModel.h"
#include "Sound/SoundClass.h"
#include "OptionsController.generated.h"

UCLASS(BlueprintType)
class PROJECT_ELYDRIS_API UOptionsController : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init(UOptionsModel* InModel);

	// UI → Controller → Model
	UFUNCTION(BlueprintCallable) void Cmd_SetResolution(FIntPoint R)     { if(Model) Model->SetResolution(R); }
	UFUNCTION(BlueprintCallable) void Cmd_SetFullscreen(EMyFullScreen M) { if(Model) Model->SetFullscreen(M); }
	UFUNCTION(BlueprintCallable) void Cmd_SetVSync(bool b)               { if(Model) Model->SetVSync(b); }
	UFUNCTION(BlueprintCallable) void Cmd_SetScalability(int32 L)        { if(Model) Model->SetScalability(L); }

	UFUNCTION(BlueprintCallable) void Cmd_SetMaster(float V) { if(Model) Model->SetMaster(V); }
	UFUNCTION(BlueprintCallable) void Cmd_SetMusic (float V) { if(Model) Model->SetMusic(V); }
	UFUNCTION(BlueprintCallable) void Cmd_SetSFX   (float V) { if(Model) Model->SetSFX(V); }
	UFUNCTION(BlueprintCallable) void Cmd_SetMouse (float V) { if(Model) Model->SetMouse(V); }

	// Botones
	UFUNCTION(BlueprintCallable) void ApplyAll();
	UFUNCTION(BlueprintCallable) void RevertFromSystem();

	// Para que el MainMenu pueda leer los valores iniciales
	UFUNCTION(BlueprintPure) UOptionsModel* GetModel() const { return Model; }

	// Asignas estas referencias en Blueprint (GameInstance o donde crees el controller)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	USoundClass* MasterClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	USoundClass* MusicClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	USoundClass* SFXClass = nullptr;

private:
	UPROPERTY()
	UOptionsModel* Model = nullptr;

	void ApplyUGameUserSettings();
	void ApplySoundClasses();
};