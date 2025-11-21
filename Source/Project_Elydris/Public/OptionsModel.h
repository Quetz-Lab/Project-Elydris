
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OptionsModel.generated.h"

UENUM(BlueprintType)
enum class EMyFullScreen : uint8
{
	FullScreen,
	WindowedFullScreen,
	Windowed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControlsChanged);

UCLASS(BlueprintType)
class PROJECT_ELYDRIS_API UOptionsModel : public UObject
{
	GENERATED_BODY()
public:

	// VIDEO
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntPoint Resolution = FIntPoint(1920, 1080);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMyFullScreen FullscreenMode = EMyFullScreen::WindowedFullScreen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bVSync = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Scalability = 3; // 0–4

	// AUDIO  (0.0–1.0)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MasterVolume = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MusicVolume = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SFXVolume = 0.8f;

	// CONTROLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MouseSensitivity = 1.0f;

	// Eventos
	UPROPERTY(BlueprintAssignable)
	FOnVideoChanged OnVideoChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAudioChanged OnAudioChanged;

	UPROPERTY(BlueprintAssignable)
	FOnControlsChanged OnControlsChanged;

	// Setters (Model cambia estado + notifica)
	UFUNCTION(BlueprintCallable)
	void SetResolution(FIntPoint InRes)
	{
		Resolution = InRes;
		OnVideoChanged.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	void SetFullscreen(EMyFullScreen Mode)
	{
		FullscreenMode = Mode;
		OnVideoChanged.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	void SetVSync(bool bInVSync)
	{
		bVSync = bInVSync;
		OnVideoChanged.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	void SetScalability(int32 Level)
	{
		Scalability = FMath::Clamp(Level, 0, 4);
		OnVideoChanged.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	void SetMaster(float V)
	{
		MasterVolume = FMath::Clamp(V, 0.f, 1.f);
		OnAudioChanged.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	void SetMusic(float V)
	{
		MusicVolume = FMath::Clamp(V, 0.f, 1.f);
		OnAudioChanged.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	void SetSFX(float V)
	{
		SFXVolume = FMath::Clamp(V, 0.f, 1.f);
		OnAudioChanged.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	void SetMouse(float V)
	{
		MouseSensitivity = FMath::Clamp(V, 0.1f, 5.f);
		OnControlsChanged.Broadcast();
	}
};
