#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateStyle.h"
#include "Components/TextBlock.h"
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
	/// hide all elements
	/// </summary>
	void HideAll();

	UFUNCTION(BlueprintCallable, Category = "Question base")
	/// <summary>
	/// hide or show notice
	/// </summary>
	/// <param name="_noticeShown">notice shown</paramn>
	void HideShowNotice(bool _noticeShown);

	UFUNCTION(BlueprintCallable, Category = "Question base")
	/// <summary>
	/// hide or show object
	/// </summary>
	void HideShowObject();

	UFUNCTION(BlueprintCallable, Category = "Question base")
	/// <summary>
	/// hide or show question
	/// </summary>
	/// <param name="_questionShown">question shown</paramn>
	void HideShowQuestion(bool _questionShown);

	UFUNCTION(BlueprintCallable, Category = "Question base")
	/// <summary>
	/// click answer at index
	/// </summary>
	/// <param name="Index">index to click</param>
	void ClickAnswer(int Index);
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// set single object reference
	/// </summary>
	/// <param name="_pObj">object reference</param>
	inline void SetObject(ASingleObject* _pObj) { m_pObject = _pObj; }

	/// <summary>
	/// set player reference
	/// </summary>
	/// <param name="_pPlayer">player reference</param>
	inline void SetPlayer(APlayerPawn* _pPlayer) { m_pPlayer = _pPlayer; }

	/// <summary>
	/// set notice text
	/// </summary>
	/// <param name="_notice">text to set</param>
	inline void SetNotice(FString _notice) { m_pNoticeButtonText->SetText(FText::FromString(_notice)); }

	/// <summary>
	/// set question text
	/// </summary>
	/// <param name="_question">text to set</param>
	inline void SetQuestion(FString _question) { m_pQuestionButtonText->SetText(FText::FromString(_question)); }
#pragma endregion

#pragma region public function
	/// <summary>
	/// set answer texts
	/// </summary>
	/// <param name="_answers">answer texts</param>
	/// <param name="_correctIndex">correct answer index</param>
	void SetAnswerTexts(TArray<FString> _answers, int _correctIndex);

	/// <summary>
	/// click on widget at position
	/// </summary>
	/// <param name="_widgetSize">size of widget</param>
	/// <param name="_widgetTransform">world transform of widget</param>
	/// <param name="_hitLocation">position</param>
	void ClickOnWidget(FVector2D _widgetSize, FTransform _widgetTransform, FVector _hitLocation);
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// notice is shown
	/// </summary>
	bool m_noticeShown;

	/// <summary>
	/// object is shown
	/// </summary>
	bool m_objectShown;

	/// <summary>
	/// question and answers are shown
	/// </summary>
	bool m_questionShown;

	/// <summary>
	/// if answer is already given
	/// </summary>
	bool m_answerGiven;

	/// <summary>
	/// correct answer index
	/// </summary>
	int m_correctAnswer;
#pragma endregion

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

	/// <summary>
	/// player reference
	/// </summary>
	APlayerPawn* m_pPlayer;
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