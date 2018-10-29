#pragma once

#pragma region system includes
#include <fstream>
#pragma endregion

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"
#include "Lesson/SingleObject.h"
#include "LessonsComponent.generated.h"
#pragma endregion

#pragma region usings
using namespace std;
#pragma endregion

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/// <summary>
/// lessons component
/// </summary>
class LTVRE_API ULessonsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	ULessonsComponent();
#pragma endregion

#pragma region UPROPERTY
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all textures for maps
	/// </summary>
	TArray<UTexture2D*> MapTextures;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all textures for single objects
	/// </summary>
	TArray<UTexture2D*> SingleObjectTextures;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all textures for object groups
	/// </summary>
	TArray<UTexture2D*> ObjectGroupTextures;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all single objects
	/// </summary>
	TArray<TSubclassOf<ASingleObject>> SingleObjectClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all basic object groups
	/// </summary>
	TArray<TSubclassOf<ASingleObject>> ObjectGroupClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all basic object groups, to identify the 2d transform for the buttons
	/// </summary>
	TArray<FLessonObjectGroup> ObjectGroupInformations;
#pragma endregion

#pragma region UFUNCTION
	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get all lessons
	/// </summary>
	/// <returns>all lessons</returns>
	TArray<FLesson> GetAllLessons();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get current lesson
	/// </summary>
	/// <returns>current lesson</returns>
	FLesson GetCurrentLesson();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set current lesson
	/// </summary>
	/// <param name="Lesson">lesson to set</param>
	void SetCurrentLesson(FLesson Lesson);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// empty the current lesson to default
	/// </summary>
	void EmptyCurrentLesson();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set name of current lesson
	/// </summary>
	/// <param name="Name">name to set</param>
	void SetLessonName(FString Name);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set creator of current lesson
	/// </summary>
	/// <param name="Creator">creator to set</param>
	void SetLessonCreator(FString Creator);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set availability of current lesson
	/// </summary>
	/// <param name="Availability">availability to set</param>
	void SetLessonAvailability(ELessonAvailability Availability);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set category of current lesson
	/// </summary>
	/// <param name="Category">category to set</param>
	void SetLessonCategory(ELessonCategory Category);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set texture name of current lesson map texture
	/// </summary>
	/// <param name="TextureName"></param>
	void SetLessonMapPicture(FString TextureName);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// save current lesson to lessons list
	/// </summary>
	/// <param name="LessonIsNew">if current lesson is new</param>
	/// <param name="Index">index of current lesson</param>
	void SaveCurrentLesson(bool LessonIsNew, int Index);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// delete current lesson at index
	/// </summary>
	/// <param name="Index">index of current lesson</param>
	void DeleteCurrentLessonAtIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get all object groups
	/// </summary>
	/// <returns>all object groups</returns>
	TArray<FLessonObjectGroup> GetAllObjectGroups();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get current object group
	/// </summary>
	/// <returns>current object group</returns>
	FLessonObjectGroup GetCurrentObjectGroup();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// empty the current object group to default
	/// </summary>
	void EmptyCurrentObjectGroup();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set name of current object group
	/// </summary>
	/// <param name="Name">name to set</param>
	void SetObjectGroupName(FString Name);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set object name of current object group
	/// </summary>
	/// <param name="Name">name to set</param>
	void SetObjectGroupObjectName(FString Name);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set object group object at index (ID)
	/// </summary>
	/// <param name="ID">index in array</param>
	/// <param name="LessonObjectName">lesson object name</param>
	void SetObjectGroupObject(int ID, FString LessonObjectName);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set current lesson object group
	/// </summary>
	/// <param name="ObjectGroup">object group to set</param>
	void SetCurrentObjectGroup(FLessonObjectGroup ObjectGroup);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// save current object group to object group list
	/// </summary>
	void SaveCurrentObjectGroup();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// delete an object group at given index
	/// </summary>
	/// <param name="Index">index of object group</param>
	/// <returns>if object group deleted</returns>
	void DeleteObjectGroupAtIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get all lesson objects
	/// </summary>
	/// <returns>all lesson objects</returns>
	TArray<FLessonObject> GetAllLessonObjects();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get current question
	/// </summary>
	/// <returns>current question</returns>
	FLessonObject GetCurrentQuestion();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set current question
	/// </summary>
	/// <param name="Question">question to set</param>
	void SetCurrentQuestion(FLessonObject Question);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set notice of current question
	/// </summary>
	/// <param name="Notice">notice to set</param>
	void SetCurrentQuestionNotice(FString Notice);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set question o current question
	/// </summary>
	/// <param name="Question">question to set</param>
	void SetCurrentQuestionQuestion(FString Question);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set answer at index of current question
	/// </summary>
	/// <param name="Index">index of answer</param>
	/// <param name="Answer">answer to set</param>
	void SetCurrentQuestionAnswer(int Index, FString Answer);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// delete current question from array
	/// </summary>
	void DeleteCurrentQuestion();
#pragma endregion

#pragma region public function
	/// <summary>
	/// load Lessons.xml
	/// </summary>
	void LoadLesson();
#pragma endregion

private:
# pragma region private variables
	/// <summary>
	/// current lesson
	/// </summary>
	FLesson m_currentLesson;

	/// <summary>
	/// lessons from this player
	/// </summary>
	TArray<FLesson> m_lessons;

	/// <summary>
	/// current object group
	/// </summary>
	FLessonObjectGroup m_currentObjectGroup;

	/// <summary>
	/// current object group name
	/// </summary>
	FString m_currentObjectGroupName;

	/// <summary>
	/// object groups created from player
	/// </summary>
	TArray<FLessonObjectGroup> m_objectGroups;

	/// <summary>
	/// all questions
	/// </summary>
	TArray<FLessonObject> m_questionCatalog;

	/// <summary>
	/// current question
	/// </summary>
	FLessonObject m_currentQuestion;

	/// <summary>
	/// lesson categories that player can edit
	/// </summary>
	TArray<ELessonCategory> m_categories;
# pragma endregion

#pragma region private function
	/// <summary>
	/// save lessons
	/// </summary>
	void SaveLesson();

	/// <summary>
	/// save current question to array
	/// </summary>
	void SaveCurrentQuestion();
#pragma endregion
};