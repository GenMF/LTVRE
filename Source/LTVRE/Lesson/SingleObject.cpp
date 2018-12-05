#pragma region project includes
#include "SingleObject.h"
#include "Player/PlayerPawn.h"
#include "UI/QuestionBase.h"
#pragma endregion

#pragma region UE4 includes
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
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

#pragma region public override function
// update every frame
void ASingleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// initialize references
	InitReferences();

	// if server disable tick and return
	if (HasAuthority())
	{
		SetActorTickEnabled(false);
		return;
	}

	// get all player
	TArray<AActor*> pFoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundActors);

	// check all players
	for (AActor* pActor : pFoundActors)
	{
		// get player reference
		APlayerPawn* pPlayer = (APlayerPawn*)pActor;

		// if current player is local player
		if (pPlayer->IsLocallyControlled())
		{
			// show question student widget
			QuestionStudent->SetVisibility(true);

			// if question shown set trace target visibility
			if (QuestionVisible)
				QuestionStudent->SetCollisionProfileName("TraceVisibility");

			// rotate widgets to player
			QuestionWidgetRotateTo(pPlayer->Camera->GetComponentLocation());

			// disable tick
			SetActorTickEnabled(false);
		}
	}
}
#pragma endregion

#pragma region UFUNCTION
// hide or show notice
void ASingleObject::HideShowNotice()
{
	// initialize references
	InitReferences();

	// if server
	if (HasAuthority())
	{
		// if practice show or hide notice at question practice
		if (m_playerStatus == EPlayerStatus::PRACTICE)
			((UQuestionBase*)(QuestionPractice->GetUserWidgetObject()))->HideShowNotice(NoticeVisible, m_playerStatus);

		// if teacher show or hide notice at question teacher
		else
			((UQuestionBase*)(QuestionTeacher->GetUserWidgetObject()))->HideShowNotice(NoticeVisible, m_playerStatus);
	}

	// if client
	else
	{
		// show or hide notice at question student
		((UQuestionBase*)(QuestionStudent->GetUserWidgetObject()))->HideShowNotice(NoticeVisible, EPlayerStatus::STUDENT);
	}
}

// hide or show question
void ASingleObject::HideShowQuestion()
{
	//initialize references
	InitReferences();

	// if server
	if (HasAuthority())
	{
		// if practice show or hide question at question practice
		if (m_playerStatus == EPlayerStatus::PRACTICE)
			((UQuestionBase*)(QuestionPractice->GetUserWidgetObject()))->HideShowQuestion(QuestionVisible, m_playerStatus);

		// if teacher show or hide question at question teacher
		else
			((UQuestionBase*)(QuestionTeacher->GetUserWidgetObject()))->HideShowQuestion(QuestionVisible, m_playerStatus);
	}

	// if client
	else
	{
		// show or hide question at question student
		((UQuestionBase*)(QuestionStudent->GetUserWidgetObject()))->HideShowQuestion(QuestionVisible, EPlayerStatus::STUDENT);

		// if question hidden set trace target none
		if (!QuestionVisible)
			QuestionStudent->SetCollisionProfileName("NoCollision");

		// if question shown set trace target visibility
		else if (QuestionVisible)
			QuestionStudent->SetCollisionProfileName("TraceVisibility");
	}
}

// set lesson object texts
void ASingleObject::SetLessonObjectTexts()
{
	// initialize references
	InitReferences();

	// set texts of widgets
	((UQuestionBase*)(QuestionPractice->GetUserWidgetObject()))->SetTexts(LessonObject);
	((UQuestionBase*)(QuestionTeacher->GetUserWidgetObject()))->SetTexts(LessonObject);
	((UQuestionBase*)(QuestionStudent->GetUserWidgetObject()))->SetTexts(LessonObject);
}

// check all players on clients implementation
void ASingleObject::CheckPlayersClient_Implementation()
{
	// if server return
	if (m_playerStatus == EPlayerStatus::PRACTICE || m_playerStatus == EPlayerStatus::TEACHER)
		return;

	// array to save all players into
	TArray<AActor*> pFoundActors;

	// get all players and save it to the array
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundActors);

	// check all players
	for (AActor* pPlayer : pFoundActors)
	{
		// if not local player continue
		if (!((APlayerPawn*)pPlayer)->IsLocallyControlled())
			continue;

		// rotate widgets to player camera
		QuestionWidgetRotateTo(((APlayerPawn*)pPlayer)->Camera->GetComponentLocation());

		// question student visible
		QuestionStudent->SetVisibility(true);

		// question student set collision profile
		QuestionStudent->SetCollisionProfileName("TraceVisibility");
	}
}

// show correct answer on clients implementation
void ASingleObject::ShowCorrectAnswerClient_Implementation()
{
	// if server return
	if (HasAuthority())
		return;

	// show correct answer on question student widget
	((UQuestionBase*)(QuestionStudent->GetUserWidgetObject()))->ShowCorrectAnswer();
}
#pragma endregion

#pragma region public function
// rotate question widgets to location
void ASingleObject::QuestionWidgetRotateTo(FVector _location)
{
	// set rotation from question widgets to location
	QuestionPractice->SetWorldRotation((_location - QuestionPractice->GetComponentLocation()).Rotation());
	QuestionTeacher->SetWorldRotation((_location - QuestionTeacher->GetComponentLocation()).Rotation());
	QuestionStudent->SetWorldRotation((_location - QuestionStudent->GetComponentLocation()).Rotation());
}

// set lesson object
void ASingleObject::SetLessonObject(FLessonObject _lessonObject)
{
	// array of numbers
	TArray<int> indices;
	TArray<int> randomIndices;

	// check all answers and add numbers
	for (int i = 0; i < _lessonObject.Answers.Num(); i++)
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
		if (!alreadyInArray)
			randomIndices.Add(randIndex);
	}

	// save old answers
	TArray<FString> oldAnswers = _lessonObject.Answers;

	// clear answers in lesson object
	_lessonObject.Answers.Empty();

	// check all random indices
	for (int i = 0; i < randomIndices.Num(); i++)
	{
		// add random answer to lesson object answers
		_lessonObject.Answers.Add(oldAnswers[randomIndices[i]]);

		// if random index is 0 set correct answer to current index
		if (randomIndices[i] == 0)
			CorrectAnswer = i;
	}

	// set lesson object
	LessonObject = _lessonObject;

	// set texts of question widgets
	SetLessonObjectTexts();
}

// set given answer
void ASingleObject::SetAnswerGiven(int _index)
{
	// set given answer
	m_answerGiven = _index;

	// array to save all players into
	TArray<AActor*> pFoundActors;

	// get all players and save it to the array
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundActors);

	// check all players
	for (AActor* pPlayer : pFoundActors)
		// if local player continue
		if (((APlayerPawn*)pPlayer)->IsLocallyControlled())
			// set answer text of player
			((APlayerPawn*)pPlayer)->SetAnswerGiven(GetName(), LessonObject.Answers[_index], _index == CorrectAnswer);
}

// show correct answer
void ASingleObject::ShowCorrectAnswer()
{
	// show correct answer on clients
	ShowCorrectAnswerClient();
}
#pragma endregion

#pragma region private function
// initialize widget
void ASingleObject::InitWidget(UWidgetComponent* _pWidget, FString _tag)
{
	// set draw size and scale of widget component
	_pWidget->SetDrawSize(FVector2D(1600.0f, 900.0f));
	_pWidget->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

	// hide widget
	_pWidget->SetVisibility(false);

	// set no collision
	_pWidget->SetCollisionProfileName("NoCollision");

	// set transparent blend mode
	_pWidget->SetBlendMode(EWidgetBlendMode::Transparent);

	// add tag
	_pWidget->ComponentTags.Add(*_tag);
}

// initialize references of widget
void ASingleObject::InitReferences()
{
	// set object reference of question widgets
	if (QuestionPractice->GetUserWidgetObject() != nullptr)
		((UQuestionBase*)(QuestionPractice->GetUserWidgetObject()))->SetObject(this);
	if (QuestionTeacher->GetUserWidgetObject() != nullptr)
		((UQuestionBase*)(QuestionTeacher->GetUserWidgetObject()))->SetObject(this);
	if (QuestionStudent->GetUserWidgetObject() != nullptr)
		((UQuestionBase*)(QuestionStudent->GetUserWidgetObject()))->SetObject(this);

	// get references of question widgets
	if (QuestionPractice->GetUserWidgetObject() != nullptr)
		((UQuestionBase*)(QuestionPractice->GetUserWidgetObject()))->GetReferences();
	if (QuestionTeacher->GetUserWidgetObject() != nullptr)
		((UQuestionBase*)(QuestionTeacher->GetUserWidgetObject()))->GetReferences();
	if (QuestionStudent->GetUserWidgetObject() != nullptr)
		((UQuestionBase*)(QuestionStudent->GetUserWidgetObject()))->GetReferences();
}
#pragma endregion

void ASingleObject::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// replicate variable
	DOREPLIFETIME(ASingleObject, Answerable);
	DOREPLIFETIME(ASingleObject, CorrectAnswer);
	DOREPLIFETIME(ASingleObject, MeshesVisible);
	DOREPLIFETIME(ASingleObject, NoticeVisible);
	DOREPLIFETIME(ASingleObject, QuestionVisible);
	DOREPLIFETIME(ASingleObject, LessonObject);
}