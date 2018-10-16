#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"
#include "Lesson/SingleObject.h"
#include "Lesson/ObjectGroup.h"
#include "LessonsComponent.generated.h"
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
	TArray<TSubclassOf<ASingleObject>> SingleObjects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all basic object groups
	/// </summary>
	TArray<TSubclassOf<AObjectGroup>> ObjectGroups;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all basic objects
	/// </summary>
	TArray<FLessonObject> LessonObjects;

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
	/// save current lesson to lessons list
	/// </summary>
	/// <param name="LessonIsNew">if current lesson is new</param>
	void SaveCurrentLesson(bool LessonIsNew);

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
	/// save current object group to object group list
	/// </summary>
	/// <param name="ObjectGroupIsNew">if current object group is new</param>
	void SaveCurrentObjectGroup(bool ObjectGroupIsNew);
#pragma endregion

private:
# pragma region private variables
	/// <summary>
	/// current lesson
	/// </summary>
	FLesson m_currentLesson;

	/// <summary>
	/// current object group
	/// </summary>
	FLessonObjectGroup m_currentObjectGroup;

	/// <summary>
	/// lesson categories that player can edit
	/// </summary>
	TArray<ELessonCategory> m_categories;

	/// <summary>
	/// object groups created from player
	/// </summary>
	TArray<FLessonObjectGroup> m_objectGroups;

	/// <summary>
	/// lessons from this player
	/// </summary>
	TArray<FLesson> m_lessons;
# pragma endregion
};