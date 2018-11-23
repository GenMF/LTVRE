#pragma region project includes
#include "QuestionBase.h"
#include "Lesson/SingleObject.h"
#include "Player/PlayerPawn.h"
#include "Game/LTVREGameInstance.h"
#pragma endregion

#pragma region UE4 includes
#include "Components/WidgetComponent.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#pragma endregion

#pragma region UFUNCTION
// set references
void UQuestionBase::SetReferences(UButton* NoticeBtn, UTextBlock* NoticeBtnTxt,
	UButton* QuestionBtn, UTextBlock* QuestionBtnTxt,
	TArray<UButton*> AnswerBtns, TArray<UTextBlock*> AnswerBtnTxts,
	UButton* ShowHideNoticeBtn, UTextBlock* ShowHideNoticeBtnTxt,
	UButton* ShowHideObjectBtn, UTextBlock* ShowHideObjectBtnTxt,
	UButton* ShowHideQuestionBtn, UTextBlock* ShowHideQuestionBtnTxt)
{
	m_pNoticeButton = NoticeBtn;
	m_pNoticeButtonText = NoticeBtnTxt;
	m_pQuestionButton = QuestionBtn;
	m_pQuestionButtonText = QuestionBtnTxt;
	m_pAnswerButtons = AnswerBtns;
	m_pAnswerButtonsText = AnswerBtnTxts;
	m_pShowHideNoticeButton = ShowHideNoticeBtn;
	m_pShowHideNoticeButtonText = ShowHideNoticeBtnTxt;
	m_pShowHideObjectButton = ShowHideObjectBtn;
	m_pShowHideObjectButtonText = ShowHideObjectBtnTxt;
	m_pShowHideQuestionButton = ShowHideQuestionBtn;
	m_pShowHideQuestionButtonText = ShowHideQuestionBtnTxt;
}

// hide or show notice
void UQuestionBase::HideShowNotice(bool _noticeShown, EPlayerStatus _status)
{
	// switch player status
	switch (_status)
	{
	// practice
	case EPlayerStatus::PRACTICE:
	{
		// if notice is already shown
		if (_noticeShown)
		{
			// show notice and set show hide notice button text
			m_pNoticeButton->SetVisibility(ESlateVisibility::Visible);

			// if show hide notice button text valid set show hide notice button text
			if (m_pShowHideNoticeButtonText != nullptr)
				m_pShowHideNoticeButtonText->SetText(FText::FromString("hide notice"));
		}

		// notice not shown
		else
		{
			// hide notice
			m_pNoticeButton->SetVisibility(ESlateVisibility::Hidden);

			// if show hide notice button text valid set show hide notice button text
			if (m_pShowHideNoticeButtonText != nullptr)
				m_pShowHideNoticeButtonText->SetText(FText::FromString("show notice"));
		}
		break;
	}

	// teacher
	case EPlayerStatus::TEACHER:
	{
		// if notice is already shown
		if (_noticeShown)
		{
			// show notice and set show hide notice button text
			m_pNoticeButton->SetStyle(ButtonNoClickShownStyle);
			m_pNoticeButtonText->SetColorAndOpacity(ButtonTextShownColor);

			// if show hide notice button text valid
			if (m_pShowHideNoticeButtonText != nullptr)
				m_pShowHideNoticeButtonText->SetText(FText::FromString("hide notice"));
		}

		// notice not shown
		else
		{
			// set notice button style hidden and set show hide notice button text
			m_pNoticeButton->SetStyle(ButtonNoClickHiddenStyle);
			m_pNoticeButtonText->SetColorAndOpacity(ButtonTextHiddenColor);

			// if show hide notice button text valid
			if (m_pShowHideNoticeButtonText != nullptr)
				m_pShowHideNoticeButtonText->SetText(FText::FromString("show notice"));
		}
		break;
	}

	// student
	case EPlayerStatus::STUDENT:
	{
		// if notice is already shown
		if (_noticeShown)
			// show notice button
			m_pNoticeButton->SetVisibility(ESlateVisibility::Visible);

		// notice not shown
		else
			// show notice button
			m_pNoticeButton->SetVisibility(ESlateVisibility::Hidden);

		break;
	}

	// default break
	default:
		break;
	}
}

// hide or show question
void UQuestionBase::HideShowQuestion(bool _questionShown, EPlayerStatus _status)
{
	// switch player status
	switch (_status)
	{
		// practice
	case EPlayerStatus::PRACTICE:
	{
		// if question is already shown
		if (_questionShown)
		{
			// show notice and set show hide notice button text
			m_pQuestionButton->SetVisibility(ESlateVisibility::Visible);

			// if show hide question button text valid
			if (m_pShowHideQuestionButtonText != nullptr)
				m_pShowHideQuestionButtonText->SetText(FText::FromString("hide question"));

			// check all answer buttons
			for (UButton* pBtn : m_pAnswerButtons)
			{
				// show button and set style
				pBtn->SetVisibility(ESlateVisibility::Visible);
				pBtn->SetStyle(ButtonClickShownStyle);
			}
		}

		// question not shown
		else
		{
			// hide notice and set show hide notice button text
			m_pQuestionButton->SetVisibility(ESlateVisibility::Hidden);

			// if show hide question button text valid
			if (m_pShowHideQuestionButtonText != nullptr)
				m_pShowHideQuestionButtonText->SetText(FText::FromString("show question"));

			// check all answer buttons and hide
			for (UButton* pBtn : m_pAnswerButtons)
				pBtn->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	}

	// teacher
	case EPlayerStatus::TEACHER:
	{
		// if question is already shown
		if (_questionShown)
		{
			// show question and set show hide question button text
			m_pQuestionButton->SetStyle(ButtonNoClickShownStyle);
			m_pQuestionButtonText->SetColorAndOpacity(ButtonTextShownColor);

			// check all answer buttons
			for (int i = 0; i < m_pAnswerButtons.Num(); i++)
			{
				// set style of button and color of button text
				m_pAnswerButtons[i]->SetStyle(ButtonClickShownStyle);
				m_pAnswerButtonsText[i]->SetColorAndOpacity(ButtonTextShownColor);

				// if current answer is correct answer set color of answer text green
				if (i == m_pObject->CorrectAnswer)
					m_pAnswerButtonsText[i]->SetColorAndOpacity(FLinearColor::Green);
			}

			// if show hide question button text valid
			if (m_pShowHideQuestionButtonText != nullptr)
				m_pShowHideQuestionButtonText->SetText(FText::FromString("hide question"));
		}

		// question not shown
		else
		{
			// set question button style hidden and set show hide question button text
			m_pQuestionButton->SetStyle(ButtonNoClickHiddenStyle);
			m_pQuestionButtonText->SetColorAndOpacity(ButtonTextHiddenColor);

			// check all answer buttons
			for (int i = 0; i < m_pAnswerButtons.Num(); i++)
			{
				// set style of button and color of button text
				m_pAnswerButtons[i]->SetStyle(ButtonClickHiddenStyle);
				m_pAnswerButtonsText[i]->SetColorAndOpacity(ButtonTextHiddenColor);

				// if current answer is correct answer set color of answer text green
				if (i == m_pObject->CorrectAnswer)
					m_pAnswerButtonsText[i]->SetColorAndOpacity(FLinearColor(0.0f, 1.0f, 0.0f, 0.5f));
			}

			// if show hide question button text valid
			if (m_pShowHideQuestionButtonText != nullptr)
				m_pShowHideQuestionButtonText->SetText(FText::FromString("show question"));
		}
		break;
	}

	// student
	case EPlayerStatus::STUDENT:
	{
		// if question is already shown
		if (_questionShown)
		{
			// show question button
			m_pQuestionButton->SetVisibility(ESlateVisibility::Visible);
			
			// show answer buttons
			for (UButton* pBtn : m_pAnswerButtons)
				pBtn->SetVisibility(ESlateVisibility::Visible);
		}

		// question not shown
		else
		{
			// hide question button
			m_pQuestionButton->SetVisibility(ESlateVisibility::Hidden);

			// hide answer buttons
			for (UButton* pBtn : m_pAnswerButtons)
				pBtn->SetVisibility(ESlateVisibility::Hidden);
		}

		break;
	}

	// default break
	default:
		break;
	}
}
#pragma endregion

#pragma region public function
// set texts from lesson object
void UQuestionBase::SetTexts(FLessonObject _lessonObj)
{
	// set notice button text
	m_pNoticeButtonText->SetText(FText::FromString(_lessonObj.Notice));

	// set question button text
	m_pQuestionButtonText->SetText(FText::FromString(_lessonObj.Question));

	// set answer button texts
	for (int i = 0; i < _lessonObj.Answers.Num(); i++)
		m_pAnswerButtonsText[i]->SetText(FText::FromString(_lessonObj.Answers[i]));
}

// show correct answer
void UQuestionBase::ShowCorrectAnswer()
{
	// check all buttons
	for (int i = 0; i < m_pAnswerButtons.Num(); i++)
	{
		// button style to set
		FButtonStyle style = ButtonClickShownStyle;

		// if current button is correct answer
		if (i == m_pObject->CorrectAnswer)
		{
			// set color of style green
			style.Normal.TintColor = FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
			style.Hovered.TintColor = FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
			style.Pressed.TintColor = FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
		}

		// if current button is given answer or given answer is -1
		else if (i == m_pObject->GetAnswerGiven() || m_pObject->GetAnswerGiven() == -1)
		{
			// set color of style red
			style.Normal.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
			style.Hovered.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
			style.Pressed.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
		}

		// set style of current answer button
		m_pAnswerButtons[i]->SetStyle(style);
	}
}

// check if trace target on widget can be clicked
bool UQuestionBase::CheckClickable(FVector2D _widgetSize, FTransform _widgetTransform, FVector _hitLocation, EPlayerStatus _status)
{
	// get relative location to ui
	FVector2D anchor = CalculatePositionRelativeToWidget(_widgetSize, _widgetTransform, _hitLocation);

	// if player status is practice
	if (_status == EPlayerStatus::PRACTICE)
		// return if trace target hit any answer button, show or hide notice or show or hide
		return ((CheckPositionInButton(anchor, m_pAnswerButtons[0]) || CheckPositionInButton(anchor, m_pAnswerButtons[1]) ||
			CheckPositionInButton(anchor, m_pAnswerButtons[2]) || CheckPositionInButton(anchor, m_pAnswerButtons[3])) &&
			m_pObject->QuestionVisible) || CheckPositionInButton(anchor, m_pShowHideNoticeButton) || 
			CheckPositionInButton(anchor, m_pShowHideQuestionButton);

	// if player status is student
	else if (_status == EPlayerStatus::STUDENT)
		// return if trace target hit any answer button
		return (CheckPositionInButton(anchor, m_pAnswerButtons[0]) || CheckPositionInButton(anchor, m_pAnswerButtons[1]) ||
			CheckPositionInButton(anchor, m_pAnswerButtons[2]) || CheckPositionInButton(anchor, m_pAnswerButtons[3])) &&
			m_pQuestionButton->IsVisible();

	// if player status is teacher
	else if (_status == EPlayerStatus::TEACHER)
		// return if trace target hit question, show hide notice, show hide object or show hide question button
		return (CheckPositionInButton(anchor, m_pQuestionButton) && m_pObject->QuestionVisible) || 
			CheckPositionInButton(anchor, m_pShowHideNoticeButton) || CheckPositionInButton(anchor, m_pShowHideObjectButton) || 
			CheckPositionInButton(anchor, m_pShowHideQuestionButton);

	// else return true
	else
		return true;
}

// click on widget at position
void UQuestionBase::ClickOnWidget(FVector2D _widgetSize, FTransform _widgetTransform, FVector _hitLocation)
{
	// get relative location to ui
	FVector2D anchor = CalculatePositionRelativeToWidget(_widgetSize, _widgetTransform, _hitLocation);

	// if anchor is in show hide object button show or hide object
	if (m_pShowHideObjectButton != nullptr && CheckPositionInButton(anchor, m_pShowHideObjectButton))
	{
		// show or hide meshes
		m_pObject->MeshesVisible = !m_pObject->MeshesVisible;

		// if meshes visible set show hide object button text to hide object
		if (m_pObject->MeshesVisible)
			m_pShowHideObjectButtonText->SetText(FText::FromString("hide object"));

		// if meshes not visible set show hide object button text to show object
		else
			m_pShowHideObjectButtonText->SetText(FText::FromString("show object"));
	}

	// if anchor is in show hide notice button show or hide notice
	else if (m_pShowHideNoticeButton != nullptr && CheckPositionInButton(anchor, m_pShowHideNoticeButton))
	{
		// show or hide notice
		m_pObject->NoticeVisible = !m_pObject->NoticeVisible;

		// call rep notify
		m_pObject->HideShowNotice();
	}

	// if anchor is in show hide question button show or hide question and answers
	else if (m_pShowHideQuestionButton != nullptr && CheckPositionInButton(anchor, m_pShowHideQuestionButton))
	{
		// show or hide question
		m_pObject->QuestionVisible = !m_pObject->QuestionVisible;

		// call rep notify
		m_pObject->HideShowQuestion();
	}

	// if anchor is in question button show correct answer
	else if (m_pQuestionButton != nullptr && CheckPositionInButton(anchor, m_pQuestionButton))
	{
		m_pObject->ShowCorrectAnswer();
	}

	// if no other button clicked check answer buttons
	else
	{
		// check all answer buttons
		for (int i = 0; i < m_pAnswerButtons.Num(); i++)
		{
			// if anchor is in answer button and no answer given set given answer
			if (CheckPositionInButton(anchor, m_pAnswerButtons[i]) && m_pObject->GetAnswerGiven() < 0)
			{
				// set given answer at index
				m_pObject->SetAnswerGiven(i);

				// if practice
				if (m_pObject->GetPlayerStatus() == EPlayerStatus::PRACTICE)
				{
					// button style to set
					FButtonStyle style = ButtonClickShownStyle;

					// set color of style green
					style.Normal.TintColor = FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
					style.Hovered.TintColor = FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
					style.Pressed.TintColor = FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
					
					// set style of answer button
					m_pAnswerButtons[m_pObject->CorrectAnswer]->SetStyle(style);

					// if given answer is not correct answer
					if (i != m_pObject->CorrectAnswer)
					{
						// set color of style red
						style.Normal.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
						style.Hovered.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
						style.Pressed.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));

						// set style of answer button
						m_pAnswerButtons[i]->SetStyle(style);
					}
				}

				// if student
				else
				{
					// button style to set
					FButtonStyle style = ButtonClickShownStyle;

					// set color of style green
					style.Normal.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
					style.Hovered.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
					style.Pressed.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));

					// set style of answer button
					m_pAnswerButtons[i]->SetStyle(style);
				}
			}
		}
	}			
}
#pragma endregion

#pragma region private function
// get 2d vector from 0,0 (upper left) to 1,1 (lower right)
FVector2D UQuestionBase::CalculatePositionRelativeToWidget(FVector2D _widgetSize, FTransform _widgetTransform, 
	FVector _hitLocation)
{
	// get relative position from hit location to widget transform
	FVector relative = _widgetTransform.InverseTransformPosition(_hitLocation);

	// return relative location to ui
	return FVector2D(FMath::Abs(1 - (relative.Y + _widgetSize.X / 2) / _widgetSize.X),
		FMath::Abs(1 - (relative.Z + _widgetSize.Y / 2) / _widgetSize.Y));
}

// check if position is in button
bool UQuestionBase::CheckPositionInButton(FVector2D _position, UButton* _pButton)
{
	// get anchors from button
	FAnchors anchors = ((UCanvasPanelSlot*)(_pButton->Slot))->GetAnchors();

	// return if position is in anchors
	return _position.X >= anchors.Minimum.X && _position.X <= anchors.Maximum.X &&
		_position.Y >= anchors.Minimum.Y && _position.Y <= anchors.Maximum.Y;
}
#pragma endregion