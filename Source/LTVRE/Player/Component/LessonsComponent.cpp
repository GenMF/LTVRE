#pragma region project includes
#include "LessonsComponent.h"
#include "Player/PlayerPawn.h"
#include "Helper/Helper.h"
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
	// array for return
	TArray<FLessonObject> lessonObjects;

	// check all lesson objects informations and add lesson object to array
	for (auto& Elem : LessonObjectInformations)
		lessonObjects.Add(Elem.Value);

	// return lesson objects
	return lessonObjects;
}

// get all lessons
TArray<FLesson> ULessonsComponent::GetAllLessons()
{
	// array for return
	TArray<FLesson> lessons;

	// check all lessons and add lesson to array
	for (auto& Elem : m_lessons)
		lessons.Add(Elem.Value);

	// return lessons
	return lessons; 
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
		m_lessons.Add(m_currentLesson.Name, m_currentLesson);

	// if current lesson is already in map
	//else
		/// TODO: fill
	
	// save lessons
	SaveLesson();
}

// get all object groups
TArray<FLessonObjectGroup> ULessonsComponent::GetAllObjectGroups()
{
	// array for return
	TArray<FLessonObjectGroup> objectGroups;

	// check all object groups and add object group to array
	for (auto& Elem : m_objectGroups)
		objectGroups.Add(Elem.Value);

	// return lessons
	return objectGroups;
}

// get current object group
FLessonObjectGroup ULessonsComponent::GetCurrentObjectGroup()
{
	return m_currentObjectGroup;
}

// empty the current object group to default
void ULessonsComponent::EmptyCurrentObjectGroup()
{
	m_currentObjectGroup = FLessonObjectGroup();

	// if no object group textures return
	if (ObjectGroupTextures.Num() <= 0)
		return;

	// set current object group picture to first available
	m_currentObjectGroup.ObjectName = ObjectGroupTextures[0]->GetName();
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

	// find lesson object from lesson object map
	for (auto& Elem : LessonObjectInformations)
		if (Elem.Value.Name.Contains(LessonObjectName))
			objGrpObj.Name = Elem.Value.Name;

	// set lesson object at index
	m_currentObjectGroup.Objects[ID] = objGrpObj;
}

// set current lesson object group
void ULessonsComponent::SetCurrentObjectGroup(FLessonObjectGroup ObjectGroup)
{
	m_currentObjectGroup = ObjectGroup;
}

// save current object group to object group list
void ULessonsComponent::SaveCurrentObjectGroup()
{
	// if current object group has no name return
	if (m_currentObjectGroup.Name.Len() <= 0)
		return;

	// if current object group allready in map replace
	if (m_objectGroups.Contains(m_currentObjectGroup.Name))
		m_objectGroups.Emplace(m_currentObjectGroup.Name, m_currentObjectGroup);

	// if not in map add to map
	else
		m_objectGroups.Add(m_currentObjectGroup.Name, m_currentObjectGroup);
	
	// empty current object group
	EmptyCurrentObjectGroup();

	// save lessons
	SaveLesson();
}

// delete an object group at given index
bool ULessonsComponent::DeleteObjectGroupAtIndex()
{
	// if current object group is in map
	if (m_objectGroups.Contains(m_currentObjectGroup.Name))
	{
		// remove current object group from map
		m_objectGroups.Remove(m_currentObjectGroup.Name);

		// return correct delete
		return true;
	}

	// return false delete
	return false;
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

	// check each lesson object and write into string
	for (auto& Elem : LessonObjectInformations)
		file << TCHAR_TO_ANSI(*Helper::StructToStringXML(Elem.Value));

	// check each object group and write into string
	for (auto& Elem : m_objectGroups)
		file << TCHAR_TO_ANSI(*Helper::StructToStringXML(Elem.Value));

	// check each lesson and write into string
	for (auto& Elem : m_lessons)
		file << TCHAR_TO_ANSI(*Helper::StructToStringXML(Elem.Value));

	// close file
	file.close();
}
#pragma endregion