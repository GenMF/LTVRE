#pragma region project includes
#include "SettingsComponent.h"  
#pragma endregion

#pragma region constructor
// constructor
USettingsComponent::USettingsComponent()
{

}
#pragma endregion

#pragma region UFUNCTION
// get name of player
FString USettingsComponent::GetName()
{
	return m_settings.m_Name;
}

// set name of player
void USettingsComponent::SetName(FString _name)
{
	// if name length is not valid return
	if (_name.Len() <= 0)
		return;

	// set player name
	m_settings.m_Name = "";

	// through all chars
	for (int i = 0; i < _name.Len(); i++)
	{
		// if char number more than 16 break for
		if (i > 15)
			break;

		// add char at index i
		m_settings.m_Name += _name[i];
	}
}

// get player is student
bool USettingsComponent::IsStudent()
{
	// return if player is student
	return m_settings.m_Type == EPlayerType::STUDENT;
}

// set player to student
void USettingsComponent::SetStudent()
{
	// set player type to student
	m_settings.m_Type = EPlayerType::STUDENT;
}

// get player is teacher
bool USettingsComponent::IsTeacher()
{
	// return if player is teacher
	return m_settings.m_Type == EPlayerType::TEACHER;
}

// set player to teacher
void USettingsComponent::SetTeacher()
{
	// set player type to teacher
	m_settings.m_Type = EPlayerType::TEACHER;
}

// get level of sound (1 - 6)
int USettingsComponent::GetSoundLevel()
{
	// if sound is 0 return 0
	if (m_settings.m_Sound == 0)
		return 0;

	// returns level of sound
	return 6 - m_settings.m_Sound / 20;
}

// set level of sound
void USettingsComponent::SetSoundLevel(int Level)
{
	// if level is not valid return
	if (Level < 1 || Level > 6)
		return;

	// set sound level
	m_settings.m_Sound = 100 - ((Level - 1) * 20);
}

// get level of music (1 - 6)
int USettingsComponent::GetMusicLevel()
{
	// if sound is 0 return 0
	if (m_settings.m_Music == 0)
		return 0;

	// returns level of sound
	return 6 - m_settings.m_Music / 20;
}

// set level of music
void USettingsComponent::SetMusicLevel(int Level)
{
	// if level is not valid return
	if (Level < 1 || Level > 6)
		return;

	// set music
	m_settings.m_Music = 100 - ((Level - 1) * 20);
}

// get level of graphic (1 - 6)
int USettingsComponent::GetGraphicLevel()
{
	// if sound is 0 return 0
	if (m_settings.m_Graphic == 0)
		return 0;

	// returns level of sound
	return 7 - m_settings.m_Graphic;
}

// set level of graphic
void USettingsComponent::SetGraphicLevel(int Level)
{
	// if level is not valid return
	if (Level < 1 || Level > 6)
		return;

	// set graphic
	m_settings.m_Graphic = 6 - (Level - 1);
}
#pragma endregion