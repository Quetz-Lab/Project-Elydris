
#include "GameManager.h"

void UGameManager::Init()
{
	Super::Init();

	OptionsModel = NewObject<UOptionsModel>(this, UOptionsModel::StaticClass());
	OptionsController = NewObject<UOptionsController>(this, UOptionsController::StaticClass());

	if (OptionsController && OptionsModel)
	{
		OptionsController->Init(OptionsModel);
		// PASO CLAVE: pasar las SoundClass al controller
		OptionsController->MasterClass = MasterSoundClass;
		OptionsController->MusicClass  = MusicSoundClass;
		OptionsController->SFXClass    = SFXSoundClass;
	}
}
