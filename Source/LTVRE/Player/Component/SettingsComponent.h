#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XmlParser/Public/FastXml.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"  
#include "SettingsComponent.generated.h"  
#pragma endregion

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/// <summary>
/// settings component
/// </summary>
class LTVRE_API USettingsComponent : public UActorComponent, public IFastXmlCallback
{
	GENERATED_BODY()

public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	USettingsComponent() {}
#pragma endregion

#pragma region public overrides
	/// <summary>
	/// get xml decleration
	/// </summary>
	/// <param name="ElementData">element data</param>
	/// <param name="XmlFileLineNumber">file line number</param>
	/// <returns>xml decleration correct processed</returns>
	virtual bool ProcessXmlDeclaration(const TCHAR * ElementData, int32 XmlFileLineNumber) override
	{
		return true;
	}

	/// <summary>
	/// get single xml element
	/// </summary>
	/// <param name="ElementName">element name</param>
	/// <param name="ElementData">element value</param>
	/// <param name="XmlFileLineNumber">file line number</param>
	/// <returns>xml element correct processed</returns>
	virtual bool ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;

	/// <summary>
	/// get single xml attribute
	/// </summary>
	/// <param name="AttributeName">attribute name</param>
	/// <param name="AttributeValue">attribute value</param>
	/// <returns>xml attribute correct processed</returns>
	virtual bool ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue) override
	{
		return true;
	}

	/// <summary>
	/// get if element scope ends
	/// </summary>
	/// <param name="Element">element</param>
	/// <returns>element scope ends</returns>
	virtual bool ProcessClose(const TCHAR* Element) override
	{
		return true;
	}

	/// <summary>
	/// get encountered comment
	/// </summary>
	/// <param name="Comment">comment</param>
	/// <returns>comment processed</returns>
	virtual bool ProcessComment(const TCHAR* Comment) override
	{
		return true;
	}
#pragma endregion

#pragma region UFUNCTION
	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// get name of player
	/// </summary>
	/// <returns>name of player</returns>
	FORCEINLINE FString GetName() { return m_settings.Name; }

	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// set name of player
	/// </summary>
	/// <param name="_name">name of player</param>
	/// <returns>name changed</returns>
	bool SetName(FString _name);

	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// get player is student
	/// </summary>
	FORCEINLINE bool IsStudent() { return m_settings.Type == EPlayerType::STUDENT; }

	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// set player to student
	/// </summary>
	void SetStudent();

	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// get player is teacher
	/// </summary>
	FORCEINLINE bool IsTeacher() { return m_settings.Type == EPlayerType::TEACHER; }

	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// set player to teacher
	/// </summary>
	void SetTeacher();

	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// get level of sound (1 - 6)
	/// </summary>
	/// <returns>level of sound</returns>
	int GetSoundLevel();

	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// set level of sound
	/// 1 is 100% sound
	/// 1 count is 20% sound
	/// 6 is 0% sound
	/// </summary>
	/// <param name="Level">level of sound</param>
	void SetSoundLevel(int Level);

	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// get level of music (1 - 6)
	/// </summary>
	/// <returns>level of music</returns>
	int GetMusicLevel();

	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// set level of music
	/// 1 is 100% music
	/// 1 count is 20% music
	/// 6 is 0% music
	/// </summary>
	/// <param name="Level">level of music</param>
	void SetMusicLevel(int Level);

	UFUNCTION(BlueprintCallable, Category = "Settins component")
	/// <summary>
	/// get level of graphic (1 - 6)
	/// </summary>
	/// <returns>level of graphic</returns>
	int GetGraphicLevel();

	UFUNCTION(BlueprintCallable, Category = "Settins component")
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

#pragma region public function
	/// <summary>
	/// load settings from file
	/// </summary>
	void LoadSettings();
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