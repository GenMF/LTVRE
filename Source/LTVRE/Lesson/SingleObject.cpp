#pragma region project includes
#include "SingleObject.h"
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

	// create root scene component
	USceneComponent* pRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = pRoot;

	// create default widget component
	QuestionPractice = CreateDefaultSubobject<UWidgetComponent>(TEXT("QuestionPractice"));
	QuestionPractice->SetupAttachment(pRoot);

	// set draw size and scale of question practice widget component
	QuestionPractice->SetDrawSize(FVector2D(1600.0f, 900.0f));
	QuestionPractice->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

	// set collision preset
	QuestionPractice->SetCollisionProfileName("TraceVisibility");
}
#pragma endregion