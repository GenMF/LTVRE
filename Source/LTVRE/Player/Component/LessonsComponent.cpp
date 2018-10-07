#pragma region project includes
#include "LessonsComponent.h" 
#pragma endregion

#pragma region constructor
// constructor
ULessonsComponent::ULessonsComponent()
{

}
#pragma endregion

#pragma region UFUNCTION
// get all lessons
TArray<FLesson> ULessonsComponent::GetAllLessons()
{
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

	// set player name
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
		// add current lesson to lesson list
		m_lessons.Add(m_currentLesson);

	// if current lesson is already in list
	//else
		/// TODO: fill
}

// get all object groups
TArray<FLessonObjectGroup> ULessonsComponent::GetAllObjectGroups()
{
	return m_objectGroups;
}
#pragma endregion