// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OptionsModel.generated.h"

UENUM(BlueprintType)
enum class EMyFullScreen : uint8
{
	FulllScreen, WindowedFullScren, Windowed
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVideoChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControlsChanged);
UCLASS()
class PROJECT_ELYDRIS_API UOptionsModel : public UObject
{
	GENERATED_BODY()
public:
	//Video
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntPoint Resolution = FIntPoint(1920, 1080);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMyFullScreen FullscreenMode = EMyFullScreen::WindowedFullScren;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bVSync = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Scalability = 3;
	//Audio
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MasterVolume = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MusicVolume = 0.8f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SFXVolume = 0.8f;
	//Controls
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MouseSensitivity = 1.0f;

	UPROPERTY(BlueprintAssignable)
	FOnVideoChanged OnVideoChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAudioChanged OnAudioChanged;
	UPROPERTY(BlueprintAssignable)
	FOnControlsChanged OnControlsChanged;

	UFUNCTION(BlueprintCallable)
	void SetMaster(float V)
	{
		MasterVolume = FMath::Clamp(V, 0.F, 1.f);
		OnAudioChanged.Broadcast();
	}
	UFUNCTION(BlueprintCallable)
	void SetMusic(float V)
	{
		MusicVolume = FMath::Clamp(V, 0.F, 1.f);
		OnAudioChanged.Broadcast();
	}
	UFUNCTION(BlueprintCallable)
	void SetSFX(float V)
	{
		SFXVolume = FMath::Clamp(V, 0.f, 1.f);
		OnAudioChanged.Broadcast();
	}
};
