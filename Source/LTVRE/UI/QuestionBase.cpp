#pragma region project includes
#include "QuestionBase.h"
#include "Lesson/SingleObject.h"
#include "Player/PlayerPawn.h"
#include "Game/LTVREGameInstance.h"
#pragma endregion

#pragma region UE4 includes
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

// hide all elements
void UQuestionBase::HideAll()
{
	// set bools to true to switch it in functions
	m_noticeShown = true;
	m_questionShown = true;
	m_objectShown = true;

	// hide notice, question and object
	HideShowNotice(false);
	HideShowQuestion(false);
	HideShowObject();
}

// hide or show notice
void UQuestionBase::HideShowNotice(bool _noticeShown)
{
	// if player null return
	if (m_pPlayer == nullptr)
		return;

	// switch player status
	switch (((ULTVREGameInstance*)(m_pPlayer->GetGameInstance()))->GetPlayerStatus())
	{
	// practice
	case EPlayerStatus::PRACTICE:
	{
		// if notice is already shown
		if (m_noticeShown)
		{
			// hide notice and set show hide notice button text
			m_pNoticeButton->SetVisibility(ESlateVisibility::Hidden);
			m_pShowHideNoticeButtonText->SetText(FText::FromString("show notice"));
		}

		// notice not shown
		else
		{
			// show notice and set show hide notice button text
			m_pNoticeButton->SetVisibility(ESlateVisibility::Visible);
			m_pShowHideNoticeButtonText->SetText(FText::FromString("hide notice"));
		}

		// set notice shown
		m_noticeShown = !m_noticeShown;
		break;
	}

	// teacher
	case EPlayerStatus::TEACHER:
	{
		// if notice is already shown
		if (m_noticeShown)
		{
			// set notice button style hidden and set show hide notice button text
			m_pNoticeButton->SetStyle(ButtonNoClickHiddenStyle);
			m_pNoticeButtonText->SetColorAndOpacity(ButtonTextHiddenColor);

			// if show hide notice button text valid
			if(m_pShowHideNoticeButtonText != nullptr)
				m_pShowHideNoticeButtonText->SetText(FText::FromString("show notice"));
		}

		// notice not shown
		else
		{
			// show notice and set show hide notice button text
			m_pNoticeButton->SetStyle(ButtonNoClickShownStyle);
			m_pNoticeButtonText->SetColorAndOpacity(ButtonTextShownColor);

			// if show hide notice button text valid
			if (m_pShowHideNoticeButtonText != nullptr)
				m_pShowHideNoticeButtonText->SetText(FText::FromString("hide notice"));
		}

		// set notice shown
		m_noticeShown = !m_noticeShown;

		// show or hide notice on clients
		m_pObject->ShowHideNoticeStudent(m_noticeShown);
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

// hide or show object
void UQuestionBase::HideShowObject()
{
	// if object shown set button text to show object
	if (m_objectShown && m_pShowHideObjectButtonText)
		m_pShowHideObjectButtonText->SetText(FText::FromString("show object"));
	
	// if object not shown set button text to hide object
	else if(m_pShowHideObjectButtonText)
		m_pShowHideObjectButtonText->SetText(FText::FromString("hide object"));

	// toggle object shown
	m_objectShown = !m_objectShown;

	// set meshes of single object visible
	m_pObject->MeshesVisible = m_objectShown;
}

// hide or show question
void UQuestionBase::HideShowQuestion(bool _questionShown)
{
	// switch player status
	switch (((ULTVREGameInstance*)(m_pPlayer->GetGameInstance()))->GetPlayerStatus())
	{
		// practice
	case EPlayerStatus::PRACTICE:
	{
		// if question is already shown
		if (m_questionShown)
		{
			// hide notice and set show hide notice button text
			m_pQuestionButton->SetVisibility(ESlateVisibility::Hidden);
			m_pShowHideQuestionButtonText->SetText(FText::FromString("show question"));

			// check all answer buttons and hide
			for (UButton* pBtn : m_pAnswerButtons)
				pBtn->SetVisibility(ESlateVisibility::Hidden);
		}

		// question not shown
		else
		{
			// show notice and set show hide notice button text
			m_pQuestionButton->SetVisibility(ESlateVisibility::Visible);
			m_pShowHideQuestionButtonText->SetText(FText::FromString("hide question"));

			// check all answer buttons
			for (UButton* pBtn : m_pAnswerButtons)
			{
				// show button and set style
				pBtn->SetVisibility(ESlateVisibility::Visible);
				pBtn->SetStyle(ButtonClickShownStyle);
			}
		}

		// set question shown
		m_questionShown = !m_questionShown;
		break;
	}

	/// TODO:
	case EPlayerStatus::TEACHER:
		break;

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

// click answer at index
void UQuestionBase::ClickAnswer(int Index)
{
	// is answer already given and not practice return
	if (m_answerGiven && ((ULTVREGameInstance*)GetGameInstance())->GetPlayerStatus() != EPlayerStatus::PRACTICE)
		return;

	// check all answer buttons
	for (int i = 0; i < m_pAnswerButtons.Num(); i++)
	{
		// button style to set
		FButtonStyle style = ButtonClickShownStyle;

		// if current index is correct answer
		if (i == m_correctAnswer)
		{
			// set color of style green
			style.Normal.TintColor = FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
			style.Hovered.TintColor = FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
			style.Pressed.TintColor = FSlateColor(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f));
		}

		// if current index is clicked index
		else if (i == Index)
		{
			// set color of style red
			style.Normal.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
			style.Hovered.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
			style.Pressed.TintColor = FSlateColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
		}

		// set style of answer button at index
		m_pAnswerButtons[i]->SetStyle(style);
	}

	// set answer given to true
	m_answerGiven = true;
}
#pragma endregion

#pragma region public function
// set answer texts
void UQuestionBase::SetAnswerTexts(TArray<FString> _answers, int _correctIndex)
{
	// check all answer texts
	for (int i = 0; i < _answers.Num(); i++)
		// set answer text of button
		m_pAnswerButtonsText[i]->SetText(FText::FromString(_answers[i]));

	// set correct answer number
	m_correctAnswer = _correctIndex;
}

// click on widget at position
void UQuestionBase::ClickOnWidget(FVector2D _widgetSize, FTransform _widgetTransform, FVector _hitLocation)
{
	// get relative location to ui
	FVector2D anchor = CalculatePositionRelativeToWidget(_widgetSize, _widgetTransform, _hitLocation);

	// if anchor is in show hide object button show or hide object
	if (CheckPositionInButton(anchor, m_pShowHideObjectButton))
		HideShowObject();

	// if anchor is in show hide notice button show or hide notice
	else if (CheckPositionInButton(anchor, m_pShowHideNoticeButton))
		HideShowNotice(false);
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