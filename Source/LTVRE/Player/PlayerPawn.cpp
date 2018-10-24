#pragma region project includes
#include "PlayerPawn.h"
#include "Component/SettingsComponent.h"
#include "Component/LessonsComponent.h"
#pragma endregion

#pragma region UE4 includes
#include "Camera/CameraComponent.h"
#pragma endregion

#pragma region constructor
// constructor
APlayerPawn::APlayerPawn()
{
	// create defaulft camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;

	// create default settings component
	Settings = CreateDefaultSubobject<USettingsComponent>(TEXT("Settings"));

	// create default lessons component
	Lessons = CreateDefaultSubobject<ULessonsComponent>(TEXT("Lessons"));

	// load settings from file
	Settings->LoadSettings();
}
#pragma endregion