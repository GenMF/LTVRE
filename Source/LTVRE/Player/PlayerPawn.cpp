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

	// create default text render component
	MenuWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Menuwidget"));
	MenuWidget->SetupAttachment(pRoot);
	MenuWidget->SetOnlyOwnerSee(true);
	MenuWidget->ComponentTags.Add("MenuWidget");

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

	// if student initialized trace from camera forward
	if (InitStudent())
		TraceForward();
}
#pragma endregion

#pragma region UFUNCTION
// initialize lesson in vr level
void APlayerPawn::InitializeLesson()
{
	// set this player to teacher
	m_isTeacher = true;

	// get current lesson
	FLesson lesson = ((ULTVREGameInstance*)GetGameInstance())->GetCurrentLesson();

	// set lesson name of result lesson
	Lessons->SetResultLessonName(lesson.Name);

	// set teacher name of result lesson
	Lessons->SetResultLessonTeacher(Settings->GetName());

	// date string and date
	FString date = "";
	FDateTime dateTime = FDateTime::Now();

	// append month, day and year
	date.Append(FString::FromInt(dateTime.GetDay()));
	date.Append("_");
	date.Append(FString::FromInt(dateTime.GetMonth()));
	date.Append("_");
	date.Append(FString::FromInt(dateTime.GetYear()));
	date.Append("_");

	// append hour, minutes and seconds
	date.Append(FString::FromInt(dateTime.GetHour()));
	date.Append("_");
	date.Append(FString::FromInt(dateTime.GetMinute()));
	date.Append("_");
	date.Append(FString::FromInt(dateTime.GetSecond()));

	// set date of result lesson
	Lessons->SetResultLessonDate(date);

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

												// lesson object for result lesson
												FLessonObject resLesson = lessonObj;

												// set object name of result question
												resLesson.ObjectName = pSingleObj->GetName();

												// add result question
												Lessons->AddResultLessonQuestion(resLesson);
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
bool APlayerPawn::SetNameTextServer_Validate(const FString& _name, FLinearColor _color, const FString& _objName)
{
	return true;
}

// set name text on server implementation
void APlayerPawn::SetNameTextServer_Implementation(const FString& _name, FLinearColor _color, const FString& _objName)
{
	// show head mesh
	HeadMesh->SetVisibility(true);

	// set text of name text
	NameText->SetText(FText::FromString(_name));

	// set color of text
	NameText->SetTextRenderColor(_color.ToFColor(true));

	// get all player
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), FoundPlayers);

	// check all players
	for (AActor* pPlayer : FoundPlayers)
	{
		// if teacher
		if (((APlayerPawn*)pPlayer)->IsTeacher())
		{
			// save text render component of current player
			UCameraComponent* pCamera = ((APlayerPawn*)pPlayer)->Camera;

			// rotate text to this
			NameText->SetWorldRotation((pCamera->GetComponentLocation() - NameText->GetComponentLocation()).Rotation());

			// if object name is given
			if (_objName != "")
			{
				// split name in name and answer
				// given is name, than \n and answer

				// name and answer text
				FString name = "";
				FString answer = "";

				// name is set
				bool nameSet = false;

				// check all chars in name
				for (int i = 0; i < _name.Len(); i++)
					// if name set add char to answer
					if (nameSet)
						answer += _name[i];

				// if answer not set and current char is not new line
					else if (_name[i] != '\n')
						name += _name[i];

				// if new line set name set true
					else
						nameSet = true;

				// set given answer of student at result lesson
				((APlayerPawn*)pPlayer)->Lessons->SetResultQuestionGivenAnswer(name, _objName, answer);

				// save lesson result to file
				((APlayerPawn*)pPlayer)->Lessons->SaveLessonResult();

				// return
				return;
			}

			// add student to result lesson of teacher
			((APlayerPawn*)pPlayer)->Lessons->AddResultLessonStudent(_name);
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

// student correctly initialized called to server validate
bool APlayerPawn::StudentInitializedServer_Validate()
{
	return true;
}

// student correctly initialized called to server implementation
void APlayerPawn::StudentInitializedServer_Implementation()
{
	// get all player
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), FoundPlayers);

	// check all players
	for (AActor* pPlayer : FoundPlayers)
		// if teacher
		if (((APlayerPawn*)pPlayer)->IsTeacher())
			// set init student of teacher
			((APlayerPawn*)pPlayer)->SetInitStudent(false);
}

// set location on clients implementation
void APlayerPawn::SetLocationClient_Implementation(FVector _location)
{
	SetActorLocation(_location);
}
#pragma endregion

#pragma region public function
// set name text with answer
void APlayerPawn::SetAnswerGiven(FString _objName, FString _text, bool _correct)
{
	// get name from settings
	FString text = Settings->GetName();

	// append new line and answer text
	text.Append("\n");
	text.Append(_text);

	// if correct answer set text on server green
	if (_correct)
		SetNameTextServer(text, FLinearColor::Green, _objName);

	// if not correct answer set text on server red
	else
		SetNameTextServer(text, FLinearColor::Red, _objName);
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

			// set visibility of menu widget
			MenuWidget->SetCollisionProfileName("TraceVisibility");
		}
	}

	// if server
	else
	{
		// if local player initialize lesson
		if (IsLocallyControlled())
		{
			InitializeLesson();

			// set visibility of menu widget
			MenuWidget->SetCollisionProfileName("TraceVisibility");
		}

		// calculate position of player
		// student 1 to 4 start at degree 0 and in 90 degree steps
		// student 5 to 8 start at degree 45 and in 90 degree steps
		// student 9 to 16 start at degree 22.5 and in 45 degree steps
		// student 17 to 32 start at degree 11.25 and in 22.5 degree steps
		// student 33 to 64 start at degree 5.625 and in 11.25 degree steps

		// get all player
		TArray<AActor*> FoundPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), FoundPlayers);

		// if player number less than 1 or 1 return
		if (FoundPlayers.Num() <= 1)
			return;

		// degree for current player
		float degree = 0.0f;

		// if player count is between 2 and 5
		if (FoundPlayers.Num() >= 2 && FoundPlayers.Num() <= 5)
			// calculate degree for current player
			degree = ((FoundPlayers.Num() - 2) % 4) * 90.0f;

		// if player count is between 6 and 9
		else if (FoundPlayers.Num() >= 6 && FoundPlayers.Num() <= 9)
			// calculate degree for current player
			degree = 45.0f + ((FoundPlayers.Num() - 2) % 4) * 90.0f;

		// if player count is between 10 and 17
		else if (FoundPlayers.Num() >= 10 && FoundPlayers.Num() <= 17)
			// calculate degree for current player
			degree = 22.5f + ((FoundPlayers.Num() - 2) % 8) * 45.0f;

		// if player count is between 18 and 33
		else if (FoundPlayers.Num() >= 18 && FoundPlayers.Num() <= 33)
			// calculate degree for current player
			degree = 11.25f + ((FoundPlayers.Num() - 2) % 16) * 22.5f;

		// if player count is between 34 and 65
		else if (FoundPlayers.Num() >= 34 && FoundPlayers.Num() <= 65)
			// calculate degree for current player
			degree = 5.625f + ((FoundPlayers.Num() - 2) % 32) * 11.25f;

		// location of teacher
		FVector location = FVector();

		// check all players
		for (AActor* pPlayer : FoundPlayers)
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

		// if local player return
		if (IsLocallyControlled())
			return;

		// get all objects
		TArray<AActor*> FoundObjects;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASingleObject::StaticClass(), FoundObjects);

		// check all object
		for (AActor* pObj : FoundObjects)
		{
			// set no collision for question widgets
			((ASingleObject*)pObj)->QuestionTeacher->SetCollisionProfileName("NoCollision");
			((ASingleObject*)pObj)->QuestionPractice->SetCollisionProfileName("NoCollision");
		}
	}
}
#pragma endregion

#pragma region private function
// initialize student on server
bool APlayerPawn::InitStudent()
{
	// if map is menu or client and not local player disable update and return false
	if (GetWorld()->GetMapName().Contains("Menu") || (!HasAuthority() && !IsLocallyControlled()))
	{
		SetActorTickEnabled(false);
		return false;
	}

	// if server
	if (HasAuthority())
	{
		// if teacher
		if (m_isTeacher)
		{
			// if student has to be initialized
			if(m_initStudent)
				// show teacher component on clients
				ShowTeacherComponentsClient(Settings->GetName());

			// return true
			return true;
		}

		// not the teacher
		else
		{
			// get all player
			TArray<AActor*> FoundPlayers;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), FoundPlayers);

			// check all players
			for (AActor* pPlayer : FoundPlayers)
				// if teacher
				if (((APlayerPawn*)pPlayer)->IsTeacher())
					// set init student of teacher
					((APlayerPawn*)pPlayer)->SetInitStudent(true);

			// disable tick
			SetActorTickEnabled(false);

			// return false
			return false;
		}
	}

	// client and local player and if student not initialized
	else if(!m_initStudent)
	{
		// get all player
		TArray<AActor*> FoundPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), FoundPlayers);

		// if any player found
		if (!FoundPlayers.Num())
			return false;

		// check all players
		for (AActor* pPlayer : FoundPlayers)
		{
			// if name text of player is not empty
			if (!((APlayerPawn*)pPlayer)->NameText->Text.IsEmpty())
			{
				// set init student true
				m_initStudent = true;

				// save text render component of current player
				UTextRenderComponent* pNameText = ((APlayerPawn*)pPlayer)->NameText;

				// rotate text to this
				pNameText->SetWorldRotation((Camera->GetComponentLocation() - pNameText->GetComponentLocation()).Rotation());
			}
		}

		// if student initialized set initialized on server
		if (m_initStudent)
			StudentInitializedServer();

		// return false
		return false;
	}
	
	// client and local player and student initialized return true
	return true;
}

// trace from camera forward
void APlayerPawn::TraceForward()
{
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

	// if hit component valid and tag is menu widget
	else if (hit.Component.IsValid() && hit.Component->ComponentHasTag("MenuWidget"))
	{
		targetID = 3;
	}

	// if target id valid
	if (targetID)
	{
		// set trace target
		m_pTraceTarget = hit.GetActor();

		// if target id is question widget target
		if (targetID == 1)
			// release widget interaction click
			WidgetInteraction->ReleasePointerKey(FKey("LeftMouseButton"));

		// check clickable true
		if (targetID == 1 && pTargetQuestionBase != nullptr &&
			pTargetQuestionBase->CheckClickable(((UWidgetComponent*)hit.GetComponent())->GetDrawSize(),
				hit.GetComponent()->GetComponentTransform(), hit.Location, status))
		{
			// increase click timer
			m_clickTimer += GetWorld()->GetDeltaSeconds();
		}

		// if trace target is object
		else if (targetID == 2 || targetID == 3)
		{
			// increase click timer
			m_clickTimer += GetWorld()->GetDeltaSeconds();
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

			// if target is 3
			else if (targetID == 3)
			{
				// get player controller
				APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				
				// if player controller valid disconnect from lesson
				if (pPlayerController)
					pPlayerController->ConsoleCommand(TEXT("disconnect"), true);
			}

			// if target id is single object target and player status is not student
			else if (status != EPlayerStatus::STUDENT)
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
	else if (m_pTraceTarget != nullptr)
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