#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"
#include "SingleObject.generated.h"  
#pragma endregion

#pragma region forward decleration
class UWidgetComponent;
class APlayerPawn;
#pragma endregion

UCLASS()
/// <summary>
/// class for a single lesson object
/// </summary>
class LTVRE_API ASingleObject : public AActor
{
	GENERATED_BODY()
	
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	ASingleObject();
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="DeltaTime">time since last frame</param>
	virtual void Tick(float DeltaTime) override;
#pragma endregion

#pragma region UPROPERTY
	UPROPERTY(Replicated)
	/// <summary>
	/// if question can be answered
	/// </summary>
	bool Answerable = true;

	UPROPERTY(Replicated)
	/// <summary>
	/// index of correct answer
	/// </summary>
	int CorrectAnswer = -1;

	UPROPERTY(ReplicatedUsing = HideShowMeshes, BlueprintReadWrite, Category = "Single object")
	/// <summary>
	/// if meshes are visible or not
	/// </summary>
	bool MeshesVisible = true;

	UPROPERTY(ReplicatedUsing = HideShowNotice)
	/// <summary>
	/// if notice is visible or not
	/// </summary>
	bool NoticeVisible = true;

	UPROPERTY(ReplicatedUsing = HideShowQuestion)
	/// <summary>
	/// if question is visible or not
	/// </summary>
	bool QuestionVisible = true;

	UPROPERTY(ReplicatedUsing = SetLessonObjectTexts)
	/// <summary>
	/// lesson object informations
	/// </summary>
	FLessonObject LessonObject = FLessonObject();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Single object")
	/// <summary>
	/// question practice widget component
	/// </summary>
	UWidgetComponent* QuestionPractice;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Single object")
	/// <summary>
	/// question teacher widget component
	/// </summary>
	UWidgetComponent* QuestionTeacher;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Single object")
	/// <summary>
	/// question student widget component
	/// </summary>
	UWidgetComponent* QuestionStudent;
#pragma endregion

#pragma region UFUNCTION
	UFUNCTION(BlueprintImplementableEvent, Category = "Single object")
	/// <summary>
	/// hide or show static meshes in blueprint
	/// </summary>
	void HideShowMeshes();

	UFUNCTION()
	/// <summary>
	/// hide or show notice
	/// </summary>
	void HideShowNotice();

	UFUNCTION()
	/// <summary>
	/// hide or show question
	/// </summary>
	void HideShowQuestion();

	UFUNCTION()
	/// <summary>
	/// set lesson object texts
	/// </summary>
	void SetLessonObjectTexts();

	UFUNCTION(NetMulticast, Reliable)
	/// <summary>
	/// check all players on clients
	/// </summary>
	void CheckPlayersClient();

	UFUNCTION(NetMulticast, Reliable)
	/// <summary>
	/// show correct answer on clients
	/// </summary>
	void ShowCorrectAnswerClient();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get player statue
	/// </summary>
	/// <returns>player status</returns>
	inline EPlayerStatus GetPlayerStatus() { return m_playerStatus; }

	/// <summary>
	/// set player status
	/// </summary>
	/// <param name="_status">status to set</param>
	inline void SetPlayerStatus(EPlayerStatus _status) { m_playerStatus = _status; }

	/// <summary>
	/// get given answer
	/// </summary>
	/// <returns>given answer index</returns>
	inline int GetAnswerGiven() { return m_answerGiven; }

	/// <summary>
	/// check all players
	/// </summary>
	inline void CheckPlayers() { CheckPlayersClient(); }
#pragma endregion

#pragma region public function
	/// <summary>
	/// rotate question widgets to location
	/// </summary>
	/// <param name="_location">location to rotate to</param>
	void QuestionWidgetRotateTo(FVector _location);

	/// <summary>
	/// set lesson object
	/// </summary>
	/// <param name="_lessonObject">lesson object to set</param>
	void SetLessonObject(FLessonObject _lessonObject);

	/// <summary>
	/// set given answer
	/// </summary>
	/// <param name="_index">index to set as given answer</param>
	void SetAnswerGiven(int _index);

	/// <summary>
	/// show correct answer
	/// </summary>
	void ShowCorrectAnswer();
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// answer index given
	/// </summary>
	int m_answerGiven = -1;
#pragma endregion

#pragma region private variable
	/// <summary>
	/// player status
	/// </summary>
	EPlayerStatus m_playerStatus = EPlayerStatus::MENU;
#pragma endregion

#pragma region private function
	/// <summary>
	/// initialize widget
	/// </summary>
	/// <param name="_pWidget">widget reference</param>
	/// <param name="_tag">tag to set</param>
	void InitWidget(UWidgetComponent* _pWidget, FString _tag);

	/// <summary>
	/// initialize references of widget
	/// </summary>
	void InitReferences();
#pragma endregion
};