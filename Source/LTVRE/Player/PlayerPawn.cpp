#pragma region project includes
#include "PlayerPawn.h"
#include "Component/SettingsComponent.h"
#include "Component/LessonsComponent.h"
#include "Game/LTVREGameInstance.h"
#include "Lesson/LocationObjectGroup.h"
#include "Lesson/Component/LocationSingleObjectComponent.h"
#include "UI/QuestionBase.h"
#include "UI/Interaction.h"
#pragma endregion

#pragma region UE4 includes
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextRenderComponent.h"
#pragma endregion

#pragma region constructor
// constructor
APlayerPawn::APlayerPawn()
{
	// create root scene component
	USceneComponent* pRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = pRoot;

	// create default camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(pRoot);

	// create default static mesh component
	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetupAttachment(Camera);
	HeadMesh->SetVisibility(false);
	HeadMesh->SetOwnerNoSee(true);
	HeadMesh->SetCollisionProfileName("NoCollision");

	// create default widget interaction component
	WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
	WidgetInteraction->SetupAttachment(Camera);

	// create default text render component
	NameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NameText"));
	NameText->SetupAttachment(pRoot);
	NameText->SetOwnerNoSee(true);

	// create default settings component
	Settings = CreateDefaultSubobject<USettingsComponent>(TEXT("Settings"));

	// create default lessons component
	Lessons = CreateDefaultSubobject<ULessonsComponent>(TEXT("Lessons"));

	// load settings from file
	Settings->LoadSettings();

	// load lessons from file
	Lessons->LoadLessons();
}
#pragma endregion

#pragma region public override function
// called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if map is menu or not local player return
	if (GetWorld()->GetMapName() == "Menu" || !IsLocallyControlled())
		return;

	// hit result
	FHitResult hit;

	// trace from camera forward
	GetWorld()->LineTraceSingleByChannel(
		hit,
		Camera->GetComponentLocation(),
		Camera->GetComponentLocation() + Camera->GetForwardVector() * 10000,
		ECollisionChannel::ECC_Visibility
	);

	// save player status
	EPlayerStatus status = ((ULTVREGameInstance*)GetGameInstance())->GetPlayerStatus();

	// save trace target to id (0 = no valid target, 1 = question widget target, 2 = single object target)
	int targetID = 0;

	// target question base
	UQuestionBase* pTargetQuestionBase = nullptr;
	
	// if hit component valid and tag correct
	if (hit.Component.IsValid() &&
		((hit.Component->ComponentHasTag("QuestionPractice") && status == EPlayerStatus::PRACTICE) ||
		(hit.Component->ComponentHasTag("QuestionTeacher") && status == EPlayerStatus::TEACHER) ||
		(hit.Component->ComponentHasTag("QuestionStudent") && status == EPlayerStatus::STUDENT)))
	{
		// set target id 1
		targetID = 1;

		// get question base
		pTargetQuestionBase = (UQuestionBase*)(((UWidgetComponent*)hit.GetComponent())->GetUserWidgetObject());
	}
	
	// if hit actor valid and tag correct
	else if (hit.Actor.IsValid() && hit.Actor->ActorHasTag("LessonObject") && status != EPlayerStatus::STUDENT)
	{
		targetID = 2;
	}

	// if target id valid
	if (targetID)
	{
		// set trace target
		m_pTraceTarget = hit.GetActor();

		// if target id is question widget target
		if(targetID == 1)
			// release widget interaction click
			WidgetInteraction->ReleasePointerKey(FKey("LeftMouseButton"));

		// check clickable true
		if (targetID == 1 && pTargetQuestionBase != nullptr &&
			pTargetQuestionBase->CheckClickable(((UWidgetComponent*)hit.GetComponent())->GetDrawSize(),
			hit.GetComponent()->GetComponentTransform(), hit.Location, status))
		{
			// increase click timer
			m_clickTimer += DeltaTime;
		}

		// if trace target is object
		else if (targetID == 2)
		{
			// increase click timer
			m_clickTimer += DeltaTime;
		}

		// if not clickable
		else
		{
			// reset click timer
			m_clickTimer = 0.0f;
		}

		// if click timer lower than time to click return
		if (m_clickTimer >= ClickTime)
		{
			// if target id is question widget target
			if (targetID == 1)
			{
				// click widget interaction
				WidgetInteraction->PressPointerKey(FKey("LeftMouseButton"));

				// get question base from hit component
				UQuestionBase* pQuestionBase = (UQuestionBase*)(((UWidgetComponent*)(hit.GetComponent()))->GetUserWidgetObject());

				// click at question base widget
				pQuestionBase->ClickOnWidget(((UWidgetComponent*)(hit.GetComponent()))->GetDrawSize(),
					hit.GetComponent()->GetComponentTransform(), hit.Location);
			}

			// if target id is single object target and player status is not student
			else if(status != EPlayerStatus::STUDENT)
			{
				// save widget component
				UWidgetComponent* pSingObj;

				// if player status is practice
				if (status == EPlayerStatus::PRACTICE)
					// widget component from question practice
					pSingObj = ((ASingleObject*)hit.GetActor())->QuestionPractice;

				// if player status is teacher
				else
					// widget component from question teacher
					pSingObj = ((ASingleObject*)hit.GetActor())->QuestionTeacher;

				// toggle question widget
				pSingObj->ToggleVisibility();

				// if question widget visible set trace visible
				if (pSingObj->IsVisible())
					pSingObj->SetCollisionProfileName("TraceVisibility");

				// if question widget not visible set no trace
				else
					pSingObj->SetCollisionProfileName("NoCollision");
			}

			// reset click timer
			m_clickTimer = 0.0f;
		}
	}

	// if trace target valid
	else if(m_pTraceTarget != nullptr)
	{
		// set trace target null and click timer 0
		m_pTraceTarget = nullptr;
		m_clickTimer = 0.0f;

		// set percentage 0 and set image percentage
		m_pInteraction->SetPercentage(0.0f);
		m_pInteraction->SetImagePercentage();
	}

	// if interaction reference valid
	if (m_pInteraction)
	{
		// set percentage of interaction widget
		m_pInteraction->SetPercentage(m_clickTimer / ClickTime * 100.0f);

		// set image percentage of interaction widget
		m_pInteraction->SetImagePercentage();
	}

	// if server set camera rotation on clients
	if (HasAuthority())
		SetCameraRotationClient(Camera->RelativeRotation);

	// if client set camera rotation on server
	else
		SetCameraRotationServer(Camera->RelativeRotation);

}
#pragma endregion

#pragma region UFUNCTION
// initialize lesson in vr level
void APlayerPawn::InitializeLesson()
{
	// get current lesson
	FLesson lesson = ((ULTVREGameInstance*)GetGameInstance())->GetCurrentLesson();

	// get all place object group actors
	TArray<AActor*> FoundPlaceObjectGroup;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALocationObjectGroup::StaticClass(), FoundPlaceObjectGroup);

	// if player status is practice or teacher initialize lesson
	if (((ULTVREGameInstance*)GetGameInstance())->GetPlayerStatus() == EPlayerStatus::PRACTICE ||
		((ULTVREGameInstance*)GetGameInstance())->GetPlayerStatus() == EPlayerStatus::TEACHER)
	{
		// check all object groups from map
		for (int i = 0; i < lesson.Map.ObjectGroups.Num(); i++)
		{
			// check all user generated object groups in lesson
			for (FLessonObjectGroup objGrp : Lessons->GetAllObjectGroups())
			{
				// if name of current user generated object group equals current group object from map
				if (objGrp.Name == lesson.Map.ObjectGroups[i])
				{
					// object group actor
					ASingleObject* pObjGrp = nullptr;

					// check all object group subclasses to spawn the right object
					for (TSubclassOf<ASingleObject> objClass : Lessons->ObjectGroupClasses)
					{
						// if name of current object class contains user generated object group object name
						if (objClass->GetName().Contains(objGrp.ObjectName))
						{
							// check all spawn places for object groups
							for (AActor* pActor : FoundPlaceObjectGroup)
							{
								// if id of spawn place is current index
								if (((ALocationObjectGroup*)(pActor))->ID == i)
								{
									// spawn object group
									pObjGrp = GetWorld()->SpawnActor<ASingleObject>(objClass, pActor->GetActorLocation(), 
										pActor->GetActorRotation());
								}
							}
						}
					}

					// if object group actor not valid break
					if (!pObjGrp)
						break;

					// check all objects of object group
					for (int j = 0; j < objGrp.Objects.Num(); j++)
					{
						// check all single object subclasses
						for (TSubclassOf<ASingleObject> singleObjClass : Lessons->SingleObjectClasses)
						{
							// if current single object class contains current object group object name
							if (singleObjClass->GetName().Contains(objGrp.Objects[j].Name))
							{
								// check current object group actor children
								for (UActorComponent* pLocSingleObjComp : pObjGrp->GetComponentsByClass(ULocationSingleObjectComponent::StaticClass()))
								{
									// if index of current location equals index of current object
									if (((ULocationSingleObjectComponent*)(pLocSingleObjComp))->ID == j)
									{
										// spawn object
										ASingleObject* pSingleObj = GetWorld()->SpawnActor<ASingleObject>(singleObjClass, 
											((USceneComponent*)pLocSingleObjComp)->GetComponentLocation(),
											((USceneComponent*)pLocSingleObjComp)->GetComponentRotation());

										// check all questions
										for (FLessonObject lessonObj : Lessons->GetAllQuestions())
										{
											// if current question is equal with current object question
											if (lessonObj.Name == objGrp.Objects[j].QuestionName)
											{
												// set player status of object
												pSingleObj->SetPlayerStatus(((ULTVREGameInstance*)GetGameInstance())->GetPlayerStatus());
												
												// hide meshes
												pSingleObj->MeshesVisible = false;
												
												// set lesson object of object
												pSingleObj->SetLessonObject(lessonObj);

												// notice visible false
												pSingleObj->NoticeVisible = false;

												// hide notice at question widget
												pSingleObj->HideShowNotice();

												// question visible false
												pSingleObj->QuestionVisible = false;

												// hide question at question widget
												pSingleObj->HideShowQuestion();

												// rotate widgets to player camera
												pSingleObj->QuestionWidgetRotateTo(Camera->GetComponentLocation());
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

// set interaction reference
void APlayerPawn::SetInteraction(UInteraction* Interaction)
{
	// set interaction widget reference
	m_pInteraction = Interaction;

	// set percentage and image percentage
	m_pInteraction->SetPercentage(0.0f);
	m_pInteraction->SetImagePercentage();
}

// initialize single objects on server validate
bool APlayerPawn::InitSingleObjectsServer_Validate()
{
	return true;
}

// initialize single objects on server implementation
void APlayerPawn::InitSingleObjectsServer_Implementation()
{
	// array to save all single objects into
	TArray<AActor*> pFoundActors;

	// get all single object and save it to the array
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASingleObject::StaticClass(), pFoundActors);

	// check all single objects
	for (AActor* pObj : pFoundActors)
		// check all players at single object
		((ASingleObject*)pObj)->CheckPlayers();
}

// set rotation on server validate
bool APlayerPawn::SetCameraRotationServer_Validate(FRotator rotation)
{
	return true;
}

// set rotation on server implementation
void APlayerPawn::SetCameraRotationServer_Implementation(FRotator rotation)
{
	// set rotation on clients
	SetCameraRotationClient(rotation);
}

// set rotation on client implementation
void APlayerPawn::SetCameraRotationClient_Implementation(FRotator rotation)
{
	// if not local player
	if (!IsLocallyControlled())
		// set local rotation of camera
		Camera->SetRelativeRotation(rotation);
}

// set name text on server validate
bool APlayerPawn::SetNameTextServer_Validate(const FString& _name, FLinearColor _color = FLinearColor::White)
{
	return true;
}

// set name text on server implementation
void APlayerPawn::SetNameTextServer_Implementation(const FString& _name, FLinearColor _color = FLinearColor::White)
{
	// show head mesh
	HeadMesh->SetVisibility(true);

	// set text of name text
	NameText->SetText(FText::FromString(_name));

	// set color of text
	NameText->SetTextRenderColor(_color.ToFColor(true));

	// array to save all players into
	TArray<AActor*> pFoundActors;

	// get all players and save it to the array
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundActors);

	// check all player
	for (AActor* pPlayer : pFoundActors)
	{
		// if local player
		if (((APlayerPawn*)pPlayer)->IsLocallyControlled())
		{
			// rotate name text to server player
			NameText->SetWorldRotation((pPlayer->GetActorLocation() - NameText->GetComponentLocation()).Rotation());

			// show head mesh on clients
			((APlayerPawn*)pPlayer)->ShowTeacherComponentsClient(((APlayerPawn*)pPlayer)->Settings->GetName());
		}
	}
}

// show head mesh and name text on clients implementation
void APlayerPawn::ShowTeacherComponentsClient_Implementation(const FString& _name)
{
	// show head mesh
	HeadMesh->SetVisibility(true);

	// set name text
	NameText->SetText(FText::FromString(_name));
}

// set location on clients implementation
void APlayerPawn::SetLocationClient_Implementation(FVector _location)
{
	SetActorLocation(_location);
}
#pragma endregion

#pragma region public function
// set name text with answer
void APlayerPawn::SetAnswerText(FString _text, bool _correct)
{
	// get name from settings
	FString text = Settings->GetName();

	// append new line and answer text
	text.Append("\n");
	text.Append(_text);

	// if correct answer set text on server green
	if (_correct)
		SetNameTextServer(text, FLinearColor::Green);

	// if not correct answer set text on server red
	else
		SetNameTextServer(text, FLinearColor::Red);
}
#pragma endregion

#pragma region protected override function
// called at begin play
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	// reset name text
	NameText->SetText(FText::FromString(""));

	// if map is menu return
	if (GetWorld()->GetMapName().Contains("Menu"))
		return;

	// if client
	if (!HasAuthority())
	{
		// if local player set name text on server
		if (IsLocallyControlled())
		{
			// set name text on server
			SetNameTextServer(Settings->GetName());

			// initialize all single objects on server
			InitSingleObjectsServer();
		}
	}

	// if server
	else
	{
		// if local player initialize lesson
		if (IsLocallyControlled())
			InitializeLesson();

		// calculate position of player
		// student 1 to 4 start at degree 0 and in 90 degree steps
		// student 5 to 8 start at degree 45 and in 90 degree steps
		// student 9 to 16 start at degree 22.5 and in 45 degree steps
		// student 17 to 32 start at degree 11.25 and in 22.5 degree steps
		// student 33 to 64 start at degree 5.625 and in 11.25 degree steps

		// get all player
		TArray<AActor*> FoundPlayer;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), FoundPlayer);

		// if player number less than 1 or 1 return
		if (FoundPlayer.Num() <= 1)
			return;

		// degree for current player
		float degree = 0.0f;

		// if player count is between 2 and 5
		if (FoundPlayer.Num() >= 2 && FoundPlayer.Num() <= 5)
			// calculate degree for current player
			degree = ((FoundPlayer.Num() - 2) % 4) * 90.0f;

		// if player count is between 6 and 9
		else if (FoundPlayer.Num() >= 6 && FoundPlayer.Num() <= 9)
			// calculate degree for current player
			degree = 45.0f + ((FoundPlayer.Num() - 2) % 4) * 90.0f;

		// if player count is between 10 and 17
		else if (FoundPlayer.Num() >= 10 && FoundPlayer.Num() <= 17)
			// calculate degree for current player
			degree = 22.5f + ((FoundPlayer.Num() - 2) % 8) * 45.0f;

		// if player count is between 18 and 33
		else if (FoundPlayer.Num() >= 18 && FoundPlayer.Num() <= 33)
			// calculate degree for current player
			degree = 11.25f + ((FoundPlayer.Num() - 2) % 16) * 22.5f;

		// if player count is between 34 and 65
		else if (FoundPlayer.Num() >= 34 && FoundPlayer.Num() <= 65)
			// calculate degree for current player
			degree = 5.625f + ((FoundPlayer.Num() - 2) % 32) * 11.25f;

		// location of teacher
		FVector location = FVector();

		// check all players
		for (AActor* pPlayer : FoundPlayer)
			// if current player is local player
			if (((APawn*)pPlayer)->IsLocallyControlled())
				// save location of teacher
				location = pPlayer->GetActorLocation();

		// set x and y location by degree and spawn distance
		location.X += SpawnDistance * FMath::Sin(FMath::DegreesToRadians(degree));
		location.Y += SpawnDistance * FMath::Cos(FMath::DegreesToRadians(degree));
		location.Z -= 25.0f;

		// set location on clients
		SetLocationClient(location);
	}
}
#pragma endregion