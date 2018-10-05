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
#pragma endregion

private:
# pragma region private variables
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