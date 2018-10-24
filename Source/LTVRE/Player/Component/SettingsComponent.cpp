#pragma region project includes
#include "SettingsComponent.h"
#include "Helper/Helper.h"
#pragma endregion

#pragma region system includes
#include <fstream>
#pragma endregion

#pragma region usings
using namespace std;
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
	return m_settings.Name;
}

// set name of player
void USettingsComponent::SetName(FString _name)
{
	// if name length is not valid return
	if (_name.Len() <= 0)
		return;

	// set player name
	m_settings.Name = "";

	// through all chars
	for (int i = 0; i < _name.Len(); i++)
	{
		// if char number more than 16 break for
		if (i > 15)
			break;

		// add char at index i
		m_settings.Name += _name[i];
	}

	// save settings
	SaveSettings();
}

// get player is student
bool USettingsComponent::IsStudent()
{
	// return if player is student
	return m_settings.Type == EPlayerType::STUDENT;
}

// set player to student
void USettingsComponent::SetStudent()
{
	// set player type to student
	m_settings.Type = EPlayerType::STUDENT;

	// save settings
	SaveSettings();
}

// get player is teacher
bool USettingsComponent::IsTeacher()
{
	// return if player is teacher
	return m_settings.Type == EPlayerType::TEACHER;

	// save settings
	SaveSettings();
}

// set player to teacher
void USettingsComponent::SetTeacher()
{
	// set player type to teacher
	m_settings.Type = EPlayerType::TEACHER;

	// save settings
	SaveSettings();
}

// get level of sound (1 - 6)
int USettingsComponent::GetSoundLevel()
{
	// if sound is 0 return 0
	if (m_settings.Sound == 0)
		return 0;

	// returns level of sound
	return 6 - m_settings.Sound / 20;

	// save settings
	SaveSettings();
}

// set level of sound
void USettingsComponent::SetSoundLevel(int Level)
{
	// if level is not valid return
	if (Level < 1 || Level > 6)
		return;

	// set sound level
	m_settings.Sound = 100 - ((Level - 1) * 20);

	// save settings
	SaveSettings();
}

// get level of music (1 - 6)
int USettingsComponent::GetMusicLevel()
{
	// if sound is 0 return 0
	if (m_settings.Music == 0)
		return 0;

	// returns level of sound
	return 6 - m_settings.Music / 20;

	// save settings
	SaveSettings();
}

// set level of music
void USettingsComponent::SetMusicLevel(int Level)
{
	// if level is not valid return
	if (Level < 1 || Level > 6)
		return;

	// set music
	m_settings.Music = 100 - ((Level - 1) * 20);

	// save settings
	SaveSettings();
}

// get level of graphic (1 - 6)
int USettingsComponent::GetGraphicLevel()
{
	// if sound is 0 return 0
	if (m_settings.Graphic == 0)
		return 0;

	// returns level of sound
	return 7 - m_settings.Graphic;

	// save settings
	SaveSettings();
}

// set level of graphic
void USettingsComponent::SetGraphicLevel(int Level)
{
	// if level is not valid return
	if (Level < 1 || Level > 6)
		return;

	// set graphic
	m_settings.Graphic = 6 - (Level - 1);

	// save settings
	SaveSettings();
}
#pragma endregion

#pragma region private function
// save settings to file
void USettingsComponent::SaveSettings()
{
	// file to write into
	ofstream file;

	// open file
	file.open(TCHAR_TO_ANSI(*Helper::GetAbsoluteFileName("Settings.xml")));
	
	// if file could not be opened return
	if (!file.is_open())
		return;

	// write into file
	file << "settings" << endl;

	// close file
	file.close();
}
#pragma endregion