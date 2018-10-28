#pragma region project includes
#include "LessonsComponent.h"
#include "Player/PlayerPawn.h"
#include "Helper/Helper.h"
#include "Helper/LessonParser.h"
#pragma endregion

#pragma region UE4 includes
#include "Engine/Texture2D.h"
#pragma endregion

#pragma region constructor
// constructor
ULessonsComponent::ULessonsComponent()
{
	
}
#pragma endregion

#pragma region UFUNCTION
// get all lesson objects
TArray<FLessonObject> ULessonsComponent::GetAllLessonObjects()
{
	// return lesson objects
	return m_questionCatalog;
}

// get all lessons
TArray<FLesson> ULessonsComponent::GetAllLessons()
{
	// return lessons
	return m_lessons;
}

// get current lesson
FLesson ULessonsComponent::GetCurrentLesson()
{
	return m_currentLesson;
}

// empty the current lesson to default
void ULessonsComponent::EmptyCurrentLesson()
{
	m_currentLesson = FLesson();
}

// set name of current lesson
void ULessonsComponent::SetLessonName(FString Name)
{
	// if name length is not valid return
	if (Name.Len() <= 0)
		return;

	// set name
	m_currentLesson.Name = "";

	// through all chars
	for (int i = 0; i < Name.Len(); i++)
	{
		// if char number more than 16 break for
		if (i > 15)
			break;

		// add char at index i
		m_currentLesson.Name += Name[i];
	}
}

// set creator of current lesson
void ULessonsComponent::SetLessonCreator(FString Creator)
{
	m_currentLesson.Creator = Creator;
}

// set availability of current lesson
void ULessonsComponent::SetLessonAvailability(ELessonAvailability Availability)
{
	m_currentLesson.Availability = Availability;
}

// set category of current lesson
void ULessonsComponent::SetLessonCategory(ELessonCategory Category)
{
	m_currentLesson.Category = Category;
}

// save current lesson to lessons list
void ULessonsComponent::SaveCurrentLesson(bool LessonIsNew)
{
	// if current lesson has no name return
	if (m_currentLesson.Name.Len() <= 0)
		return;

	// if current lesson is a new lesson
	if (LessonIsNew)
		// add current lesson to lesson map
		m_lessons.Add(m_currentLesson);

	// if current lesson is already in map
	//else
		/// TODO: fill
	
	// save lessons
	SaveLesson();
}

// get all object groups
TArray<FLessonObjectGroup> ULessonsComponent::GetAllObjectGroups()
{
	// return lessons
	return m_objectGroups;
}

// get current object group
FLessonObjectGroup ULessonsComponent::GetCurrentObjectGroup()
{
	return m_currentObjectGroup;
}

// empty the current object group to default
void ULessonsComponent::EmptyCurrentObjectGroup()
{
	// set current object group default lesson object group
	m_currentObjectGroup = FLessonObjectGroup();

	// if no object group textures return
	if (ObjectGroupTextures.Num() <= 0)
		return;

	// set current object group picture to first available
	m_currentObjectGroup.ObjectName = ObjectGroupTextures[0]->GetName();

	// empty current object group name
	m_currentObjectGroupName = "";
}

// set name of current object group
void ULessonsComponent::SetObjectGroupName(FString Name)
{
	// if name length is not valid return
	if (Name.Len() <= 0)
		return;

	// set name
	m_currentObjectGroup.Name = "";

	// through all chars
	for (int i = 0; i < Name.Len(); i++)
	{
		// if char number more than 16 break for
		if (i > 15)
			break;

		// add char at index i
		m_currentObjectGroup.Name += Name[i];
	}
}

// set picture name of current object group
void ULessonsComponent::SetObjectGroupObjectName(FString Name)
{
	// if name length is not valid return
	if (Name.Len() <= 0)
		return;

	// set name
	m_currentObjectGroup.ObjectName = Name;
}

// set object group object at index (ID)
void ULessonsComponent::SetObjectGroupObject(int ID, FString LessonObjectName)
{
	// while array length is lower than id add new lesson object
	while (m_currentObjectGroup.Objects.Num() < ID + 1)
		m_currentObjectGroup.Objects.Add(FObjectGroupObject());

	// object group object to set
	FObjectGroupObject objGrpObj;

	// set name of object group object
	objGrpObj.Name = LessonObjectName;

	// set lesson object at index
	m_currentObjectGroup.Objects[ID] = objGrpObj;
}

// set current lesson object group
void ULessonsComponent::SetCurrentObjectGroup(FLessonObjectGroup ObjectGroup)
{
	// set current object group name
	m_currentObjectGroupName = ObjectGroup.Name;

	// set current object group
	m_currentObjectGroup = ObjectGroup;
}

// save current object group to object group list
void ULessonsComponent::SaveCurrentObjectGroup()
{
	// if current object group has no name return
	if (m_currentObjectGroup.Name.Len() <= 0)
		return;

	// if current object group name is empty
	if (m_currentObjectGroupName == "")
	{
		// add current object group to array
		m_objectGroups.Add(m_currentObjectGroup);
	}

	//if current object group name valid
	else
	{
		// check all object groups, if name equals replace object group
		for (int i = 0; i < m_objectGroups.Num(); i++)
			if (m_objectGroups[i].Name == m_currentObjectGroupName)
				m_objectGroups[i] = m_currentObjectGroup;
	}
	
	// empty current object group
	EmptyCurrentObjectGroup();

	// save lessons
	SaveLesson();
}

// delete an object group at given index
void ULessonsComponent::DeleteObjectGroupAtIndex(int Index)
{
	m_objectGroups.RemoveAt(Index);
}
#pragma endregion

#pragma region public function
// load Lessons.xml
void ULessonsComponent::LoadLesson()
{
	// file to lesson parser
	FileToLessonParser ftlp;

	// error saves
	FText errorText;
	int errorNumber;

	// parse xml file into file to string parser
	if (!FFastXml::ParseXmlFile(&ftlp, *Helper::GetAbsoluteFileName("Lessons.xml"),
		nullptr, nullptr, false, false, errorText, errorNumber))
	{
		// log errors
		GLog->Log("LTVRE", ELogVerbosity::Error, FString("Error: ").Append(errorText.ToString()));
		GLog->Log("LTVRE", ELogVerbosity::Error, FString("Error number: ") + FString::FromInt(errorNumber));
	}

	// set arrays from parser to component
	m_questionCatalog = ftlp.m_LessonObjects;
	m_objectGroups = ftlp.m_LessonObjectGroups;
	m_lessons = ftlp.m_Lessons;
}
#pragma endregion

#pragma region private function
// save lessons and object groups to file
void ULessonsComponent::SaveLesson()
{
	// file to write into
	ofstream file;

	// open file
	file.open(TCHAR_TO_ANSI(*Helper::GetAbsoluteFileName("Lessons.xml")));

	// if file could not be opened return
	if (!file.is_open())
		return;

	// check each question and write into string
	for (auto& Elem : m_questionCatalog)
		file << TCHAR_TO_ANSI(*Helper::StructToStringXML(Elem));

	// check each object group and write into string
	for (auto& Elem : m_objectGroups)
		file << TCHAR_TO_ANSI(*Helper::StructToStringXML(Elem));

	// check each lesson and write into string
	for (auto& Elem : m_lessons)
		file << TCHAR_TO_ANSI(*Helper::StructToStringXML(Elem));

	// close file
	file.close();
}

// load all lesson objects from xml
void LoadLessonObjects(FString _lessonObjectsXML)
{

}

// load all lesson object Groups from xml
void LoadLessonObjectGroups(FString _lessonObjectGroupsXML)
{

}

// load all lessons from xml
void LoadLessons(FString _lessonsXML)
{

}
#pragma endregion