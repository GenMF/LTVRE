#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"  
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
#pragma endregion

private:
# pragma region private variables
	/// <summary>
	/// current lesson
	/// </summary>
	FLesson m_currentLesson;

	/// <summary>
	/// lesson categories that player can edit
	/// </summary>
	TArray<ELessonCategory> m_categories;

	/// <summary>
	/// lessons from this player
	/// </summary>
	TArray<FLesson> m_lessons;
# pragma endregion
};