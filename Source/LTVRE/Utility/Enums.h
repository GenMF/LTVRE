#pragma once

#pragma region player
/// <summary>
/// type of player
/// </summary>
enum class EPlayerType
{
	NONE,
	STUDENT,
	TEACHER
};
#pragma endregion

#pragma region lesson
/// <summary>
/// availability of lesson
/// </summary>
enum class ELessonAvailability
{
	NONE,
	VISIBLE,
	ANSWERABLE
};

/// <summary>
/// category of lesson
/// </summary>
enum class ELessonCategory
{
	NONE,
	HISTORY
};

/// <summary>
/// map of lesson
/// </summary>
enum class ELessonMap
{
	NONE,
	CASTLE
};
#pragma endregion