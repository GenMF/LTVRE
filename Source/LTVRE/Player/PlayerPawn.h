#pragma once

// project includes
#include "Utility/Structs.h"
#include "Component/SettingsComponent.h"

// UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "PlayerPawn.generated.h"

UCLASS()
/// <summary>
/// player
/// </summary>
class LTVRE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	/// <summary>
	/// constructor
	/// </summary>
	APlayerPawn();

#pragma region UPROPERTY
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Player Pawn")
	/// <summary>
	/// camera component of player
	/// </summary>
	UCameraComponent* Camera;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Player Pawn")
	/// <summary>
	/// setting component of player
	/// </summary>
	USettingsComponent* Settings;
#pragma endregion

private:
# pragma region private variables
	/// <summary>
	/// lesson categories that player can edit
	/// </summary>
	list<ELessonCategory> m_categories;

	/// <summary>
	/// lessons from this player
	/// </summary>
	list<FLesson> m_lessons;
# pragma endregion
};