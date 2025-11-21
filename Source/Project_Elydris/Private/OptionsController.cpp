#include "OptionsController.h"
#include "GameFramework/GameUserSettings.h"

void UOptionsController::Init(UOptionsModel* InModel)
{
	Model = InModel;
	RevertFromSystem(); // sistema → model al arrancar
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
			SC->Properties.Volume = V;
		}
	};

	SetVol(MasterClass, Model->MasterVolume);
	SetVol(MusicClass,  Model->MusicVolume);
	SetVol(SFXClass,    Model->SFXVolume);
}

void UOptionsController::ApplyAll()
{
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
