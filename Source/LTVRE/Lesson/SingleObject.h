#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"
#include "SingleObject.generated.h"  
#pragma endregion

UCLASS()
/// <summary>
/// class for a single lesson object
/// </summary>
class LTVRE_API ASingleObject : public AActor
{
	GENERATED_BODY()
	
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	ASingleObject();
#pragma endregion

#pragma region UFUNCTION
	UFUNCTION(BlueprintCallable, Category = "Single object")
	/// <summary>
	/// get notice of lesson object
	/// </summary>
	/// <returns>notice of lesson object</returns>
	FORCEINLINE FString GetLessonObjectNotice()
	{
		return m_lessonObject.Notice;
	}

	UFUNCTION(BlueprintCallable, Category = "Single object")
	/// <summary>
	/// get question of lesson object
	/// </summary>
	/// <returns>notice of lesson object</returns>
	FORCEINLINE FString GetLessonObjectQuestion()
	{
		return m_lessonObject.Question;
	}

	UFUNCTION(BlueprintCallable, Category = "Single object")
	/// <summary>
	/// get answers of lesson object
	/// </summary>
	/// <returns>answers of lesson object</returns>
	FORCEINLINE TArray<FString> GetLessonObjectAnswers()
	{
		return m_lessonObject.Answers;
	}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// set lesson object
	/// </summary>
	/// <param name="_lessonObject">lesson object to set</param>
	void SetLessonObject(FLessonObject _lessonObject)
	{
		m_lessonObject = _lessonObject;
	}
#pragma endregion

protected:
#pragma region protected variables
	/// <summary>
	/// lesson object informations
	/// </summary>
	FLessonObject m_lessonObject;
#pragma endregion
};