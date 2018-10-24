#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"  
#include "SettingsComponent.generated.h"  
#pragma endregion

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/// <summary>
/// settings component
/// </summary>
class LTVRE_API USettingsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	USettingsComponent();
#pragma endregion

#pragma region UFUNCTION
	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// get name of player
	/// </summary>
	/// <returns>name of player</returns>
	FString GetName();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// set name of player
	/// </summary>
	/// <param name="_name">name of player</param>
	void SetName(FString _name);

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// get player is student
	/// </summary>
	bool IsStudent();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// set player to student
	/// </summary>
	void SetStudent();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// get player is teacher
	/// </summary>
	bool IsTeacher();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// set player to teacher
	/// </summary>
	void SetTeacher();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// get level of sound (1 - 6)
	/// </summary>
	/// <returns>level of sound</returns>
	int GetSoundLevel();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// set level of sound
	/// 1 is 100% sound
	/// 1 count is 20% sound
	/// 6 is 0% sound
	/// </summary>
	/// <param name="Level">level of sound</param>
	void SetSoundLevel(int Level);

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// get level of music (1 - 6)
	/// </summary>
	/// <returns>level of music</returns>
	int GetMusicLevel();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// set level of music
	/// 1 is 100% music
	/// 1 count is 20% music
	/// 6 is 0% music
	/// </summary>
	/// <param name="Level">level of music</param>
	void SetMusicLevel(int Level);

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// get level of graphic (1 - 6)
	/// </summary>
	/// <returns>level of graphic</returns>
	int GetGraphicLevel();

	UFUNCTION(BlueprintCallable)
	/// <summary>
	/// set level of graphic
	/// 1 is highest graphic
	/// 6 is lowest graphic
	/// </summary>
	/// <param name="Level">level of graphic</param>
	void SetGraphicLevel(int Level);
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get player type
	/// </summary>
	/// <returns>player type</returns>
	inline EPlayerType GetPlayerType() { return m_settings.Type; }

	/// <summary>
	/// get sound percentage
	/// </summary>
	/// <returns>sound percentage</returns>
	inline int GetSoundPercentage() { return m_settings.Sound; }

	/// <summary>
	/// get music percentage
	/// </summary>
	/// <returns>music percentage</returns>
	inline int GetMusicPercentage() { return m_settings.Music; }
#pragma endregion

private:
#pragma region private variables
	/// <summary>
	/// settings of player
	/// </summary>
	FPlayerSettings m_settings;
#pragma endregion

#pragma region private function
	/// <summary>
	/// save settings to file
	/// </summary>
	void SaveSettings();
#pragma endregion
};