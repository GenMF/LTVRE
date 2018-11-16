#pragma region project includes
#include "SingleObject.h"
#include "Player/PlayerPawn.h"
#include "UI/QuestionBase.h"
#pragma endregion

#pragma region UE4 includes
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealNetwork.h"
#pragma endregion

#pragma region constructor
// constructor
ASingleObject::ASingleObject()
{
	// set replicates in network
	bReplicates = true;

	// create root scene component
	USceneComponent* pRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = pRoot;

	// add actor tag
	Tags.Add("LessonObject");

	// create default widget component and initialize
	QuestionPractice = CreateDefaultSubobject<UWidgetComponent>(TEXT("QuestionPractice"));
	QuestionPractice->SetupAttachment(pRoot);
	InitWidget(QuestionPractice, "QuestionPractice");

	// create default widget component and initialize
	QuestionTeacher = CreateDefaultSubobject<UWidgetComponent>(TEXT("QuestionTeacher"));
	QuestionTeacher->SetupAttachment(pRoot);
	InitWidget(QuestionTeacher, "QuestionTeacher");

	// create default widget component and initialize
	QuestionStudent = CreateDefaultSubobject<UWidgetComponent>(TEXT("QuestionStudent"));
	QuestionStudent->SetupAttachment(pRoot);
	InitWidget(QuestionStudent, "QuestionStudent");
}
#pragma endregion

#pragma region UFUNCTION
// show or hide notice of student on clients implementation
void ASingleObject::ShowHideNoticeStudentClient_Implementation(bool _noticeShown)
{
	// if client
	if (!HasAuthority())
	{
		// hide or show notice
		((UQuestionBase*)QuestionStudent->GetUserWidgetObject())->HideShowNotice(_noticeShown);

		// if question student not visible show widget
		if (!QuestionStudent->IsVisible())
			QuestionStudent->SetVisibility(true);
	}
}

// show or hide question of student on clients implementation
void ASingleObject::ShowHideQuestionStudentClient_Implementation(bool _questionShown)
{
	// if client
	if (!HasAuthority())
	{
		// hide or show question
		((UQuestionBase*)QuestionStudent->GetUserWidgetObject())->HideShowQuestion(_questionShown);

		// if question student not visible show widget
		if(!QuestionStudent->IsVisible())
			QuestionStudent->SetVisibility(true);

		// if question shown set trace visibility
		if (_questionShown)
			QuestionStudent->SetCollisionProfileName("TraceVisibility");

		// if question hidden set trace no collision
		else
			QuestionStudent->SetCollisionProfileName("NoCollision");
	}
}

// show correct answer for student on clients implementation
void ASingleObject::ShowCorrectAnswerClient_Implementation()
{
	// if server return
	if (HasAuthority())
		return;

	// show correct answer on question student
	((UQuestionBase*)(QuestionStudent->GetUserWidgetObject()))->ShowCorrectAnswer();
}

// check all players to init widget on clients implementation
void ASingleObject::CheckAllPlayersForInitClient_Implementation()
{
	// if server return
	if (HasAuthority())
		return;

	// get all actor objects
	TArray<AActor*> pFoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundPlayers);

	// check all player
	for (AActor* pPlayer : pFoundPlayers)
	{
		// if player is local player
		if (((APlayerPawn*)pPlayer)->IsLocallyControlled())
		{
			// initialize widget
			((APlayerPawn*)pPlayer)->InitWidget((UQuestionBase*)(QuestionStudent->GetUserWidgetObject()), this);

			// hide question and notice button
			((UQuestionBase*)(QuestionStudent->GetUserWidgetObject()))->HideShowNotice(false);
			((UQuestionBase*)(QuestionStudent->GetUserWidgetObject()))->HideShowQuestion(false);
		}
	}
}
#pragma endregion

#pragma region public function
// set lesson object
void ASingleObject::SetLessonObject(FLessonObject _lessonObject)
{
	// set lesson object
	LessonObject = _lessonObject;

	// array of numbers
	TArray<int> indices;
	TArray<int> randomIndices;

	// check all answers and add numbers
	for (int i = 0; i < LessonObject.Answers.Num(); i++)
		indices.Add(i);

	// while random indices not all set
	while (randomIndices.Num() < indices.Num())
	{
		// random index
		int randIndex = FMath::RandRange(0, indices.Num() - 1);

		// if rand index is already in array
		bool alreadyInArray = false;

		// check all random indices and if random index already in array continue
		for (int i = 0; i < randomIndices.Num(); i++)
			if (randomIndices[i] == randIndex)
				alreadyInArray = true;

		// if not already in array add random index to new random indices
		if(!alreadyInArray)
			randomIndices.Add(randIndex);
	}

	// save old answers
	TArray<FString> oldAnswers = LessonObject.Answers;

	// clear answers in lesson object
	LessonObject.Answers.Empty();

	// check all random indices
	for (int i = 0; i < randomIndices.Num(); i++)
	{
		// add random answer to lesson object answers
		LessonObject.Answers.Add(oldAnswers[randomIndices[i]]);

		// if random index is 0 set correct answer to current index
		if (randomIndices[i] == 0)
			CorrectAnswer = i;
	}
}

// toggle question widget visibility
void ASingleObject::ToggleQuestionWidget(EPlayerStatus _status)
{
	// switch player status
	switch (_status)
	{
	// practice status
	case EPlayerStatus::PRACTICE:
	{
		// toggle question practice widget visibility
		QuestionPractice->ToggleVisibility();

		// set collision preset of question practice widget
		QuestionPractice->SetCollisionProfileName("TraceVisibility");
		break;
	}

	// practice status
	case EPlayerStatus::TEACHER:
		// toggle question teacher widget visibility
		QuestionTeacher->ToggleVisibility();

		// set collision preset of question teacher widget
		QuestionTeacher->SetCollisionProfileName("TraceVisibility");
		break;

	// default
	default:
		break;
	}
}

// show or hide notice of student
void ASingleObject::ShowHideNoticeStudent(bool _noticeShown)
{
	// show or hide notice of student on clients
	ShowHideNoticeStudentClient(_noticeShown);
}

// show or hide question of student
void ASingleObject::ShowHideQuestionStudent(bool _questionShown)
{
	// show or hide question of student on clients
	ShowHideQuestionStudentClient(_questionShown);
}

// rotate question widgets to location
void ASingleObject::QuestionWidgetRotateTo(FVector _location)
{
	// set rotation from question widgets to location
	QuestionPractice->SetWorldRotation((_location - QuestionPractice->GetComponentLocation()).Rotation());
	QuestionTeacher->SetWorldRotation((_location - QuestionTeacher->GetComponentLocation()).Rotation());
	QuestionStudent->SetWorldRotation((_location - QuestionTeacher->GetComponentLocation()).Rotation());
}

// show correct answer for students
void ASingleObject::ShowCorrectAnswer()
{
	// show correct answer student on clients
	ShowCorrectAnswerClient();
}

// check all players to init widget
void ASingleObject::CheckAllPlayersForInit()
{
	// check all player to init widget on clients
	CheckAllPlayersForInitClient();
}
#pragma endregion

#pragma region private function
// initialize widget
void ASingleObject::InitWidget(UWidgetComponent* _pWidget, FString _tag)
{
	// set draw size and scale of widget component
	_pWidget->SetDrawSize(FVector2D(1600.0f, 900.0f));
	_pWidget->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

	// set no collision and hide widget
	_pWidget->SetCollisionProfileName("NoCollision");
	_pWidget->SetVisibility(false);

	// set transparent blend mode
	_pWidget->SetBlendMode(EWidgetBlendMode::Transparent);

	// add tag
	_pWidget->ComponentTags.Add(*_tag);
}
#pragma endregion

void ASingleObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// replicate variable
	DOREPLIFETIME(ASingleObject, MeshesVisible);
	DOREPLIFETIME(ASingleObject, LessonObject);
	DOREPLIFETIME(ASingleObject, CorrectAnswer);
}