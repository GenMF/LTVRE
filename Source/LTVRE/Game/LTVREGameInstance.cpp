#pragma region project includes
#include "LTVREGameInstance.h" 
#pragma endregion

#pragma region UFUNCTION
// get current lesson
FLesson ULTVREGameInstance::GetCurrentLesson()
{
	return m_currentLesson;
}

// set current lesson
void ULTVREGameInstance::SetCurrentLesson(FLesson Lesson)
{
	m_currentLesson = Lesson;
}
#pragma endregion