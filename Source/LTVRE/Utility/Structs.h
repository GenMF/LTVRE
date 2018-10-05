#pragma once

#pragma region UE4 includes
#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"  
#pragma endregion

#pragma region project includes
#include "Utility/Enums.h"
#include "Structs.generated.h"
#pragma endregion

#pragma region usings
using namespace std;
#pragma endregion

#pragma region player
USTRUCT(BlueprintType)
/// <summary>
/// player settings
/// </summary>
struct FPlayerSettings
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Player settings")
	/// <summary>
	/// name of player
	/// </summary>
	FString Name = "Player";

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Player settings")
	/// <summary>
	/// type of player
	/// </summary>
	EPlayerType Type;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Player settings")
	/// <summary>
	/// sound level
	/// </summary>
	int Sound = 100;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Player settings")
	/// <summary>
	/// music level
	/// </summary>
	int Music = 100;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Player settings")
	/// <summary>
	/// graphic level
	/// </summary>
	int Graphic = 6;
};
#pragma endregion

#pragma region lesson
USTRUCT(BlueprintType)
/// <summary>
/// single object from a lesson
/// </summary>
struct FLessonObject
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// name of object
	/// </summary>
	FString Name;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// transform of object relative to group
	/// </summary>
	FTransform Transform;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// picture of object
	/// </summary>
	UTexture2D* Picture;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// static mesh of object
	/// </summary>
	UStaticMesh* StaticMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// skeletal mesh of object
	/// </summary>
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// notice to this object
	/// </summary>
	FString Notice;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// question to this object
	/// </summary>
	FString Question;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// answers for the question
	/// </summary>
	TArray<FString> Answers;
};

USTRUCT(BlueprintType)
/// <summary>
/// group of objects from a lesson
/// </summary>
struct FLessonObjectGroup
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object group")
	/// <summary>
	/// name of object group
	/// </summary>
	FString Name;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object group")
	/// <summary>
	/// picture of object group
	/// </summary>
	UTexture2D* Picture;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object group")
	/// <summary>
	/// objects
	/// </summary>
	TArray<FLessonObject> Objects;
};

USTRUCT(BlueprintType)
/// <summary>
/// map from a lesson
/// </summary>
struct FLessonMap
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson map")
	/// <summary>
	/// type of map
	/// </summary>
	ELessonMap Map;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson map")
	/// <summary>
	/// picture of map
	/// </summary>
	UTexture2D* Picture;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson map")
	/// <summary>
	/// transform for object groups 2D
	/// </summary>
	TMap<int, FTransform> Transform2D;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson map")
	/// <summary>
	/// object groups to id
	/// </summary>
	TMap<int, FLessonObjectGroup> ObjectGroupID;
};

USTRUCT(BlueprintType)
/// <summary>
/// lesson
/// </summary>
struct FLesson
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson")
	/// <summary>
	/// name of lesson
	/// </summary>
	FString Name;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson")
	/// <summary>
	/// creator of lesson
	/// </summary>
	FString Creator;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson")
	/// <summary>
	/// availability of lesson
	/// </summary>
	ELessonAvailability Availability;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson")
	/// <summary>
	/// category of lesson
	/// </summary>
	ELessonCategory Category;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson")
	/// <summary>
	/// map of lesson
	/// </summary>
	FLessonMap Map;
};
#pragma endregion