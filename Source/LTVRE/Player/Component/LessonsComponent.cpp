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
#pragma region delete
	m_lessons.Empty();

	FLesson lesson;
	lesson.Name = "First";
	lesson.Creator = "Marc";
	m_lessons.Add(lesson);

	lesson.Name = "Second";
	lesson.Creator = "Marc";
	m_lessons.Add(lesson);

	lesson.Name = "Third";
	lesson.Creator = "Marc";
	m_lessons.Add(lesson);
#pragma endregion
	return m_lessons; 
}
#pragma endregion