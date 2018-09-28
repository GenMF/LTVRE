#pragma once

#pragma region system includes
#include <list>
#include <map>  
#pragma endregion

#pragma region UE4 includes
#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"  
#pragma endregion

#pragma region project includes
#include "Utility/Enums.h"  
#pragma endregion

#pragma region usings
using namespace std;
#pragma endregion

#pragma region player
/// <summary>
/// player settings
/// </summary>
struct FPlayerSettings
{
	/// <summary>
	/// name of player
	/// </summary>
	FString m_Name = "Player";

	/// <summary>
	/// type of player
	/// </summary>
	EPlayerType m_Type;

	/// <summary>
	/// sound level
	/// </summary>
	int m_Sound = 100;

	/// <summary>
	/// music level
	/// </summary>
	int m_Music = 100;

	/// <summary>
	/// graphic level
	/// </summary>
	int m_Graphic = 6;
};
#pragma endregion

#pragma region lesson
/// <summary>
/// single object from a lesson
/// </summary>
struct FLessonObject
{
	/// <summary>
	/// name of object
	/// </summary>
	FString m_Name;

	/// <summary>
	/// transform of object relative to group
	/// </summary>
	FTransform m_Transform;

	/// <summary>
	/// picture of object
	/// </summary>
	UTexture2D* m_PPicture;

	/// <summary>
	/// static mesh of object
	/// </summary>
	UStaticMesh* m_PStaticMesh;

	/// <summary>
	/// skeletal mesh of object
	/// </summary>
	USkeletalMesh* m_PSkeletalMesh;

	/// <summary>
	/// notice to this object
	/// </summary>
	FString m_Notice;

	/// <summary>
	/// question to this object
	/// </summary>
	FString m_Question;

	/// <summary>
	/// answers for the question
	/// </summary>
	list<FString> Answers;
};

/// <summary>
/// group of objects from a lesson
/// </summary>
struct FLessonObjectGroup
{
	/// <summary>
	/// name of object group
	/// </summary>
	FString m_Name;

	/// <summary>
	/// picture of object group
	/// </summary>
	UTexture2D* m_PPicture;

	/// <summary>
	/// objects
	/// </summary>
	list<FLessonObject> m_Objects;
};

/// <summary>
/// map from a lesson
/// </summary>
struct FLessonMap
{
	/// <summary>
	/// type of map
	/// </summary>
	ELessonMap m_Map;

	/// <summary>
	/// picture of map
	/// </summary>
	UTexture2D* m_PPicture;

	/// <summary>
	/// transform for object groups 2D
	/// </summary>
	map<int, FTransform> m_Transform2D;

	/// <summary>
	/// object groups to id
	/// </summary>
	map<int, FLessonObjectGroup> m_ObjectGroupID;
};

/// <summary>
/// lesson
/// </summary>
struct FLesson
{
	/// <summary>
	/// name of lesson
	/// </summary>
	FString m_Name;

	/// <summary>
	/// availability of lesson
	/// </summary>
	ELessonAvailability m_Availability;

	/// <summary>
	/// category of lesson
	/// </summary>
	ELessonCategory m_Category;

	/// <summary>
	/// map of lesson
	/// </summary>
	FLessonMap m_Map;
};
#pragma endregion