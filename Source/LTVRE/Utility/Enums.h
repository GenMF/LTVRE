#pragma once

#pragma region player
UENUM(BlueprintType)
/// <summary>
/// type of player
/// </summary>
enum class EPlayerType : uint8
{
	STUDENT	UMETA(DisplayName = "Student"),
	TEACHER	UMETA(Displayname = "Teacher")
};
#pragma endregion

#pragma region lesson
UENUM(BlueprintType)
/// <summary>
/// availability of lesson
/// </summary>
enum class ELessonAvailability : uint8
{
	INVISIBLE	UMETA(DisplayName = "Invisible"),
	VISIBLE		UMETA(DisplayName = "Visible"),
	ANSWERABLE	UMETA(DisplayName = "Answerable")
};

UENUM(BlueprintType)
/// <summary>
/// category of lesson
/// </summary>
enum class ELessonCategory : uint8
{
	NONE	UMETA(DisplayName = "None"),
	HISTORY	UMETA(DisplayName = "History")
};

UENUM(BlueprintType)
/// <summary>
/// map of lesson
/// </summary>
enum class ELessonMap : uint8
{
	EMPTY	UMETA(DisplayName = "Empty"),
	CASTLE	UMETA(DisplayName = "Castle")
};
#pragma endregion