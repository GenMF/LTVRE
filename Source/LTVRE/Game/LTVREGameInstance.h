#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Engine/GameInstance.h" 
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"
#include "LTVREGameInstance.generated.h" 
#pragma endregion

UCLASS()
/// <summary>
/// game instance
/// </summary>
class LTVRE_API ULTVREGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
#pragma region UFUNCTION
	UFUNCTION(BlueprintCallable, Category = "LTVRE game instance")
	/// <summary>
	/// get status of player
	/// </summary>
	/// <returns>status of player</returns>
	EPlayerStatus GetPlayerStatus();

	UFUNCTION(BlueprintCallable, Category = "LTVRE game instance")
	/// <summary>
	/// set player status
	/// </summary>
	/// <param name="Status">status to set</param>
	void SetPlayerStatus(EPlayerStatus Status);

	UFUNCTION(BlueprintCallable, Category = "LTVRE game instance")
	/// <summary>
	/// get current lesson
	/// </summary>
	/// <returns>current lesson</returns>
	FLesson GetCurrentLesson();

	UFUNCTION(BlueprintCallable, Category = "LTVRE game instance")
	/// <summary>
	/// set current lesson
	/// </summary>
	/// <param name=""Lesson>lesson to set</param>
	void SetCurrentLesson(FLesson Lesson);
#pragma endregion
	
private:
#pragma region private variables
	/// <summary>
	/// status of player
	/// </summary>
	EPlayerStatus m_status;

	/// <summary>
	/// current lesson
	/// </summary>
	FLesson m_currentLesson;
#pragma endregion
};