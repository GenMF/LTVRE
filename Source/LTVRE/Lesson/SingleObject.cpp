#pragma region project includes
#include "SingleObject.h"
#include "Player/PlayerPawn.h"
#pragma endregion

#pragma region UE4 includes
#include "Components/WidgetComponent.h"
#pragma endregion

#pragma region constructor
// constructor
ASingleObject::ASingleObject()
{
	// set replicates in network
	bReplicates = true;

	// actor can tick
	PrimaryActorTick.bCanEverTick = true;

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
}
#pragma endregion

#pragma region public override function
// called every frame
void ASingleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if player not valid return
	if (!m_pPlayer)
		return;

	// set rotation from question widgets to player camera
	QuestionPractice->SetWorldRotation((m_pPlayer->GetActorLocation() - QuestionPractice->GetComponentLocation()).Rotation());
	QuestionTeacher->SetWorldRotation((m_pPlayer->GetActorLocation() - QuestionTeacher->GetComponentLocation()).Rotation());
}
#pragma endregion

#pragma region public function
// set lesson object
void ASingleObject::SetLessonObject(FLessonObject _lessonObject)
{
	// set lesson object
	m_lessonObject = _lessonObject;

	// array of numbers
	TArray<int> indices;
	TArray<int> randomIndices;

	// check all answers and add numbers
	for (int i = 0; i < m_lessonObject.Answers.Num(); i++)
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
	TArray<FString> oldAnswers = m_lessonObject.Answers;

	// clear answers in lesson object
	m_lessonObject.Answers.Empty();

	// check all random indices
	for (int i = 0; i < randomIndices.Num(); i++)
	{
		// add random answer to lesson object answers
		m_lessonObject.Answers.Add(oldAnswers[randomIndices[i]]);

		// if random index is 0 set correct answer to current index
		if (randomIndices[i] == 0)
			m_correctAnswer = i;
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