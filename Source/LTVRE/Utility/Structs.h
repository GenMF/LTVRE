#pragma once

#pragma region project includes
#include "Utility/Enums.h"
#include "Structs.generated.h"
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
	EPlayerType Type = EPlayerType::STUDENT;

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
	FString Name = "";

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// object name of object
	/// </summary>
	FString ObjectName = "";

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// notice to this object
	/// </summary>
	FString Notice = "";

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// question to this object
	/// </summary>
	FString Question = "";

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object")
	/// <summary>
	/// answers for the question
	/// </summary>
	TArray<FString> Answers;
};

USTRUCT(BlueprintType)
/// <summary>
/// object group of objects from a lesson
/// </summary>
struct FObjectGroupObject
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Object group object")
	/// <summary>
	/// name of lesson object
	/// </summary>
	FString Name = "";

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Object group object")
	/// <summary>
	/// question name of object
	/// </summary>
	FString QuestionName = "";
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
	FString Name = "";

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object group")
	/// <summary>
	/// name of picture of object group
	/// </summary>
	FString ObjectName = "";

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object group")
	/// <summary>
	/// vector 2D for objects 2D
	/// </summary>
	TArray<FVector2D> Transform2D;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson object group")
	/// <summary>
	/// objects
	/// </summary>
	TArray<FObjectGroupObject> Objects;
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
	/// name of picture of map
	/// </summary>
	FString Picture = "";

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson map 2D")
	/// <summary>
	/// vector 2D for object groups 2D
	/// </summary>
	TArray<FVector2D> Transform2D;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson map 2D")
	/// <summary>
	/// object groups
	/// </summary>
	TArray<FString> ObjectGroups;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson map 2D")
	/// <summary>
	/// lesson object transforms
	/// </summary>
	TArray<FTransform> LessonObjectTransforms;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson map VR")
	/// <summary>
	/// lesson object names
	/// </summary>
	TArray<FString> LessonObjectNames;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson map VR")
	/// <summary>
	/// lesson object object names
	/// </summary>
	TArray<FString> LessonObjectObjectNames;
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
	FString Name = "";
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson")
	/// <summary>
	/// creator of lesson
	/// </summary>
	FString Creator = "this";

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson")
	/// <summary>
	/// availability of lesson
	/// </summary>
	ELessonAvailability Availability = ELessonAvailability::INVISIBLE;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson")
	/// <summary>
	/// category of lesson
	/// </summary>
	ELessonCategory Category = ELessonCategory::NONE;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Lesson")
	/// <summary>
	/// map of lesson
	/// </summary>
	FLessonMap Map = FLessonMap();
};

/// <summary>
/// answer of student
/// </summary>
struct FResultStudentAnswer
{
	/// <summary>
	/// name of student
	/// </summary>
	FString m_Name = "";

	/// <summary>
	/// given answer
	/// </summary>
	FString m_GivenAnswer = "";
};

/// <summary>
/// question in result
/// </summary>
struct FResultQuestion
{
	/// <summary>
	/// question information
	/// </summary>
	FLessonObject m_Question = FLessonObject();

	/// <summary>
	/// students answer
	/// </summary>
	TArray<FResultStudentAnswer> m_StudentsAnswer;
};

/// <summary>
/// result of current lesson
/// </summary>
struct FLessonResult
{
	/// <summary>
	/// name of lesson
	/// </summary>
	FString m_LessonName = "";

	/// <summary>
	/// start time and date of lesson
	/// </summary>
	FString m_LessonDate = "";

	/// <summary>
	/// name of teacher
	/// </summary>
	FString m_TeacherName = "";

	/// <summary>
	/// all questions
	/// </summary>
	TArray<FResultQuestion> m_Questions;
};
#pragma endregion