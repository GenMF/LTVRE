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

#pragma region UPROPERTY
	UPROPERTY(ReplicatedUsing = HideShowMeshes, BlueprintReadWrite, Category = "Single object")
	/// <summary>
	/// if meshes are visible or not
	/// </summary>
	bool MeshesVisible = true;

	UPROPERTY(Replicated)
	/// <summary>
	/// lesson object informations
	/// </summary>
	FLessonObject LessonObject;

	UPROPERTY(Replicated)
	/// <summary>
	/// index of correct answer
	/// </summary>
	int CorrectAnswer;

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

	UFUNCTION(NetMulticast, Reliable)
	/// <summary>
	/// show or hide notice of student on clients
	/// </summary>
	/// <param name="_noticeShown">notice shown</paramn>
	void ShowHideNoticeStudentClient(bool _noticeShown);

	UFUNCTION(NetMulticast, Reliable)
	/// <summary>
	/// show or hide question of student on clients
	/// </summary>
	/// <param name="_questionShown">question shown</paramn>
	void ShowHideQuestionStudentClient(bool _questionShown);
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// set player reference
	/// </summary>
	/// <param name="_pPlayer">player reference</param>
	inline void SetPlayer(APlayerPawn* _pPlayer) { m_pPlayer = _pPlayer; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// set lesson object
	/// </summary>
	/// <param name="_lessonObject">lesson object to set</param>
	void SetLessonObject(FLessonObject _lessonObject);

	/// <summary>
	/// toggle question widget visibility
	/// </summary>
	/// <param name="_status">player status</param>
	void ToggleQuestionWidget(EPlayerStatus _status);

	/// <summary>
	/// show or hide notice of student
	/// </summary>
	/// <param name="_noticeShown">notice shown</param>
	void ShowHideNoticeStudent(bool _noticeShown);

	/// <summary>
	/// show or hide question of student
	/// </summary>
	/// <param name="_questionShown">question shown</param>
	void ShowHideQuestionStudent(bool _questionShown);

	/// <summary>
	/// rotate question widgets to location
	/// </summary>
	/// <param name="_location">location to rotate to</param>
	void QuestionWidgetRotateTo(FVector _location);
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// player reference
	/// </summary>
	APlayerPawn* m_pPlayer;
#pragma endregion

#pragma region private function
	/// <summary>
	/// initialize widget
	/// </summary>
	/// <param name="_pWidget">widget reference</param>
	/// <param name="_tag">tag to set</param>
	void InitWidget(UWidgetComponent* _pWidget, FString _tag);
#pragma endregion
};