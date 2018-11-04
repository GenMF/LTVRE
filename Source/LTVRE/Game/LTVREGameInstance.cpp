#pragma region project includes
#include "LTVREGameInstance.h" 
#pragma endregion

#pragma region UFUNCTION
// get status of player
EPlayerStatus ULTVREGameInstance::GetPlayerStatus()
{
	return m_status;
}

// set player status
void ULTVREGameInstance::SetPlayerStatus(EPlayerStatus Status)
{
	m_status = Status;
}

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