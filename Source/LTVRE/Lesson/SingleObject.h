#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"
#include "SingleObject.generated.h"  
#pragma endregion

#pragma region forward decleration
class UWidgetComponent;
class APlayerPawn;
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

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="DeltaTime">time since last frame</param>
	virtual void Tick(float DeltaTime) override;
#pragma endregion

#pragma region UPROPERTY
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Single object")
	/// <summary>
	/// question practice widget component
	/// </summary>
	UWidgetComponent* QuestionPractice;
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
	/// get index of correct answer
	/// </summary>
	/// <returns>index of correct answer</returns>
	inline int GetCorrectAnswer() { return m_correctAnswer; }

	/// <summary>
	/// set player reference
	/// </summary>
	/// <param name="_pPlayer">player reference</param>
	inline void SetPlayer(APlayerPawn* _pPlayer) { m_pPlayer = _pPlayer; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// set lesson object
	/// </summary>
	/// <param name="_lessonObject">lesson object to set</param>
	void SetLessonObject(FLessonObject _lessonObject);
#pragma endregion

private:
#pragma region private primitive variables
	/// <summary>
	/// index of correct answer
	/// </summary>
	int m_correctAnswer;
#pragma endregion

#pragma region private variables
	/// <summary>
	/// lesson object informations
	/// </summary>
	FLessonObject m_lessonObject;
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// player reference
	/// </summary>
	APlayerPawn* m_pPlayer;
#pragma endregion
};