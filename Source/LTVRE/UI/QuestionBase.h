#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateStyle.h"
#include "Components/TextBlock.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"
#include "QuestionBase.generated.h"
#pragma endregion

#pragma region forward decleration
class UButton;
class ASingleObject;
class APlayerPawn;
#pragma endregion

UCLASS()
/// <summary>
/// question widget base class
/// </summary>
class LTVRE_API UQuestionBase : public UUserWidget
{
	GENERATED_BODY()

public:
#pragma region UPROPERTY
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Question base")
	/// <summary>
	/// color for button text if shown
	/// </summary>
	FLinearColor ButtonTextShownColor = FLinearColor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Question base")
	/// <summary>
	/// color for button text if hidden
	/// </summary>
	FLinearColor ButtonTextHiddenColor = FLinearColor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Question base")
	/// <summary>
	/// style for shown button that can not be clicked
	/// </summary>
	FButtonStyle ButtonNoClickShownStyle = FButtonStyle();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Question base")
	/// <summary>
	/// style for hidden button that can not be clicked
	/// </summary>
	FButtonStyle ButtonNoClickHiddenStyle = FButtonStyle();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Question base")
	/// <summary>
	/// style for shown button that can be clicked
	/// </summary>
	FButtonStyle ButtonClickShownStyle = FButtonStyle();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Question base")
	/// <summary>
	/// style for hidden button that can be clicked
	/// </summary>
	FButtonStyle ButtonClickHiddenStyle = FButtonStyle();
#pragma endregion

#pragma region UFUNCTION
	UFUNCTION(BlueprintImplementableEvent, Category = "Question base")
	/// <summary>
	/// get references from widget
	/// </summary>
	void GetReferences();

	UFUNCTION(BlueprintCallable, Category = "Question base")
	/// <summary>
	/// set references
	/// </summary>
	/// <param name="NoticeBtn">notice button</param>
	/// <param name="NoticeBtnTxt">notice button text</param>
	/// <param name="QuestionBtn">question button</param>
	/// <param name="QuestionBtnTxt">question button text</param>
	/// <param name="AnswerBtns">answer buttons</param>
	/// <param name="AnswerBtnTxts">answer button texts</param>
	/// <param name="ShowHideNoticeBtn">show or hide notice button</param>
	/// <param name="ShowHideNoticeBtnTxt">show or hide notice button text</param>
	/// <param name="ShowHideObjectBtn">show or hide object button</param>
	/// <param name="ShowHideObjectBtnTxt">show or hide object button text</param>
	/// <param name="ShowHideQuestionBtn">show or hide question button</param>
	/// <param name="ShowHideQuestionBtnTxt">show or hide question button text</param>
	void SetReferences(UButton* NoticeBtn, UTextBlock* NoticeBtnTxt, 
		UButton* QuestionBtn, UTextBlock* QuestionBtnTxt,
		TArray<UButton*> AnswerBtns, TArray<UTextBlock*> AnswerBtnTxts,
		UButton* ShowHideNoticeBtn, UTextBlock* ShowHideNoticeBtnTxt,
		UButton* ShowHideObjectBtn, UTextBlock* ShowHideObjectBtnTxt,
		UButton* ShowHideQuestionBtn, UTextBlock* ShowHideQuestionBtnTxt);

	UFUNCTION(BlueprintCallable, Category = "Question base")
	/// <summary>
	/// hide or show notice
	/// </summary>
	/// <param name="_noticeShown">notice shown</paramn>
	/// <param name="_statue">player statue</paramn>
	void HideShowNotice(bool _noticeShown, EPlayerStatus _status);

	UFUNCTION(BlueprintCallable, Category = "Question base")
	/// <summary>
	/// hide or show question
	/// </summary>
	/// <param name="_questionShown">question shown</paramn>
	/// <param name="_statue">player statue</paramn>
	void HideShowQuestion(bool _questionShown, EPlayerStatus _status);
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// set single object reference
	/// </summary>
	/// <param name="_pObj">object reference</param>
	inline void SetObject(ASingleObject* _pObj) { m_pObject = _pObj; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// set texts from lesson object
	/// </summary>
	/// <param name="_lessonObj">lesson object</param>
	void SetTexts(FLessonObject _lessonObj);

	/// <summary>
	/// show correct answer
	/// </summary>
	void ShowCorrectAnswer();

	/// <summary>
	/// check if trace target on widget can be clicked
	/// </summary>
	/// <param name="_widgetSize">size of widget</param>
	/// <param name="_widgetTransform">world transform of widget</param>
	/// <param name="_hitLocation">position</param>
	/// <param name="_status">status of player</param>
	/// <returns>if trace target can be clicked</returns>
	bool CheckClickable(FVector2D _widgetSize, FTransform _widgetTransform, FVector _hitLocation, EPlayerStatus _status);

	/// <summary>
	/// click on widget at position
	/// </summary>
	/// <param name="_widgetSize">size of widget</param>
	/// <param name="_widgetTransform">world transform of widget</param>
	/// <param name="_hitLocation">position</param>
	void ClickOnWidget(FVector2D _widgetSize, FTransform _widgetTransform, FVector _hitLocation);
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// notice button
	/// </summary>
	UButton* m_pNoticeButton;

	/// <summary>
	/// notice button text
	/// </summary>
	UTextBlock* m_pNoticeButtonText;

	/// <summary>
	/// question button
	/// </summary>
	UButton* m_pQuestionButton;

	/// <summary>
	/// question button text
	/// </summary>
	UTextBlock* m_pQuestionButtonText;

	/// <summary>
	/// answer buttons
	/// </summary>
	TArray<UButton*> m_pAnswerButtons;

	/// <summary>
	/// answer buttons text
	/// </summary>
	TArray<UTextBlock*> m_pAnswerButtonsText;

	/// <summary>
	/// show or hide notice button
	/// </summary>
	UButton* m_pShowHideNoticeButton;

	/// <summary>
	/// show or hide notice button text
	/// </summary>
	UTextBlock* m_pShowHideNoticeButtonText;

	/// <summary>
	/// show or hide object button
	/// </summary>
	UButton* m_pShowHideObjectButton;

	/// <summary>
	/// show or hide object button text
	/// </summary>
	UTextBlock* m_pShowHideObjectButtonText;

	/// <summary>
	/// show or hide question button
	/// </summary>
	UButton* m_pShowHideQuestionButton;

	/// <summary>
	/// show or hide question button text
	/// </summary>
	UTextBlock* m_pShowHideQuestionButtonText;

	/// <summary>
	/// object
	/// </summary>
	ASingleObject* m_pObject;
#pragma endregion

#pragma region private function
	/// <summary>
	/// get 2d vector from -0.5,-0.5 (upper left) to 0.5,0.5 (lower right)
	/// </summary>
	/// <param name="_widgetSize">size of widget</param>
	/// <param name="_widgetTransform">world transform of widget</param>
	/// <param name="_hitLocation">world location of hit</param>
	/// <returns>2d vector relative to ui</returns>
	FVector2D CalculatePositionRelativeToWidget(FVector2D _widgetSize, FTransform _widgetTransform, FVector _hitLocation);

	/// <summary>
	/// check if position is in button
	/// </summary>
	/// <param name="_position">position to check</param>
	/// <param name="_pButton">button</param>
	/// <returns>in button or not</returns>
	bool CheckPositionInButton(FVector2D _position, UButton* _pButton);
#pragma endregion
};