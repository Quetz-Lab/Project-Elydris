#include "OptionsController.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
void UOptionsController::Init(UOptionsModel* InModel)
{
	Model = InModel;
	RevertFromSystem(); // sistema → model al arrancar

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 3.f, FColor::Green,
			TEXT("C++: OptionsController::Init() llamado")
		);
	}
}

static EWindowMode::Type ToWindowMode(EMyFullScreen M)
{
	switch (M)
	{
	case EMyFullScreen::FullScreen:         return EWindowMode::Fullscreen;
	case EMyFullScreen::WindowedFullScreen: return EWindowMode::WindowedFullscreen;
	default:                                return EWindowMode::Windowed;
	}
}

void UOptionsController::ApplyUGameUserSettings()
{
	if (!Model) return;

	if (UGameUserSettings* GS = GEngine->GetGameUserSettings())
	{
		GS->SetScreenResolution(Model->Resolution);
		GS->SetFullscreenMode(ToWindowMode(Model->FullscreenMode));
		GS->SetVSyncEnabled(Model->bVSync);
		GS->SetOverallScalabilityLevel(Model->Scalability);
		GS->ApplySettings(false);
		GS->SaveSettings();
	}
}

void UOptionsController::ApplySoundClasses()
{
	if (!Model) return;

	auto SetVol = [](USoundClass* SC, float V)
	{
		if (SC)
		{
			SC->Properties.Volume = FMath::Clamp(V, 0.f, 1.f);
		}
	};

	SetVol(MasterClass, Model->MasterVolume);
	SetVol(MusicClass,  Model->MusicVolume);
	SetVol(SFXClass,    Model->SFXVolume);
}

void UOptionsController::ApplyAll()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 2.f, FColor::Yellow,
			TEXT("C++: ApplyAll() llamado")
		);
	}

	ApplyUGameUserSettings();
	ApplySoundClasses();
}


void UOptionsController::RevertFromSystem()
{
	if (!Model) return;

	if (UGameUserSettings* GS = GEngine->GetGameUserSettings())
	{
		Model->SetResolution(GS->GetScreenResolution());
		Model->SetVSync(GS->IsVSyncEnabled());
		Model->SetScalability(GS->GetOverallScalabilityLevel());

		EMyFullScreen MyMode = EMyFullScreen::Windowed;
		auto WM = GS->GetFullscreenMode();
		if (WM == EWindowMode::Fullscreen)          MyMode = EMyFullScreen::FullScreen;
		else if (WM == EWindowMode::WindowedFullscreen) MyMode = EMyFullScreen::WindowedFullScreen;

		Model->SetFullscreen(MyMode);
	}

	// Aquí podrías también restaurar audio / sensibilidad desde un SaveGame si quieres.
}
