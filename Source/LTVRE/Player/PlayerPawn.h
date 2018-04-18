#pragma once

// project includes
#include "Utility/Structs.h"

// UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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

private:
# pragma region private variables
	/// <summary>
	/// name of player
	/// </summary>
	FString m_name;

	/// <summary>
	/// type of player
	/// </summary>
	EPlayerType m_type;

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