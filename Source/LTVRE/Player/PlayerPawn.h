#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"
#include "Component/SettingsComponent.h"  
#include "PlayerPawn.generated.h"  
#pragma endregion

UCLASS()
/// <summary>
/// player
/// </summary>
class LTVRE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	APlayerPawn();
#pragma endregion

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