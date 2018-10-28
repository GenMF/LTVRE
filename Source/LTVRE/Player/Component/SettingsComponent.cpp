#pragma region project includes
#include "SettingsComponent.h"
#include "Helper/Helper.h"
#pragma endregion

#pragma region UE4 includes
#include "XmlParser/Public/FastXml.h"
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

#pragma region public overrides
// get single xml element
bool USettingsComponent::ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber)
{
	// save element name in string
	FString name = ElementName;

	// set name from xml element
	if (name == "Name")
		SetName(ElementData);

	// set type from xml element
	else if (name == "Type")
		m_settings.Type = (EPlayerType)FMath::Max(FMath::Min(FCString::Atoi(ElementData), 0), 1);

	// set sound from xml element
	else if (name == "Sound")
		SetSoundLevel(FMath::Max(FMath::Min(FCString::Atoi(ElementData), 6), 1));

	// set music from xml element
	else if (name == "Music")
		SetMusicLevel(FMath::Max(FMath::Min(FCString::Atoi(ElementData), 6), 1));

	// set graphic from xml element
	else if (name == "Graphic")
		SetGraphicLevel(FMath::Max(FMath::Min(FCString::Atoi(ElementData), 6), 1));

	// return true
	return true;
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
		return 1;

	// returns level of sound
	return 1 + m_settings.Sound / 20;
}

// set level of sound
void USettingsComponent::SetSoundLevel(int Level)
{
	// if level is not valid return
	if (Level < 1 || Level > 6)
		return;

	// set sound level
	m_settings.Sound = (Level - 1) * 20;

	// save settings
	SaveSettings();
}

// get level of music (1 - 6)
int USettingsComponent::GetMusicLevel()
{
	// if sound is 0 return 0
	if (m_settings.Music == 0)
		return 1;

	// returns level of music
	return 1 + m_settings.Music / 20;
}

// set level of music
void USettingsComponent::SetMusicLevel(int Level)
{
	// if level is not valid return
	if (Level < 1 || Level > 6)
		return;

	// set music
	m_settings.Music = (Level - 1) * 20;

	// save settings
	SaveSettings();
}

// get level of graphic (1 - 6)
int USettingsComponent::GetGraphicLevel()
{
	// returns level of graphic
	return m_settings.Graphic;
}

// set level of graphic
void USettingsComponent::SetGraphicLevel(int Level)
{
	// if level is not valid return
	if (Level < 1 || Level > 6)
		return;

	// set graphic
	m_settings.Graphic = Level;

	// save settings
	SaveSettings();
}
#pragma endregion

#pragma region public function
// load settings from file
void USettingsComponent::LoadSettings()
{
	// error saves
	FText errorText;
	int errorNumber;

	// parse xml file into this
	if (!FFastXml::ParseXmlFile(this, *Helper::GetAbsoluteFileName("Settings.xml"), 
		nullptr, nullptr, false, false, errorText, errorNumber))
	{
		// log errors
		GLog->Log("LTVRE", ELogVerbosity::Error, FString("Error: ").Append(errorText.ToString()));
		GLog->Log("LTVRE", ELogVerbosity::Error, FString("Error number: ") + FString::FromInt(errorNumber));
	}
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

	// write settings xml string into file
	file << TCHAR_TO_ANSI(*Helper::StructToStringXML(m_settings));

	// close file
	file.close();
}
#pragma endregion