#pragma region project includes
#include "PlayerPawn.h"  
#pragma endregion

#pragma region constructor
// constructor
APlayerPawn::APlayerPawn()
{
	// create defaulft camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// create default settings component
	Settings = CreateDefaultSubobject<USettingsComponent>(TEXT("Settings"));
}
#pragma endregion