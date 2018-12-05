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

	// if student initialized
	if (InitStudent())
	{
		// trace from camera forward
		TraceForward();

		// set rotation of menu widget
		MenuWidget->SetRelativeRotation(FRotator(90.0f, 0.0f, -Camera->RelativeRotation.Yaw + 180.0f));
	}
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
				// if name of current user generated object group not equals current group object from map continue
				if (objGrp.Name != lesson.Map.ObjectGroups[i])
					continue;

				// object group actor
				ASingleObject* pObjGrp = nullptr;

				// check all object group subclasses to spawn the right object
				for (TSubclassOf<ASingleObject> objClass : Lessons->ObjectGroupClasses)
				{
					// if name of current object class not contains user generated object group object name continue
					if (!objClass->GetName().Contains(objGrp.ObjectName))
						continue;

					// check all spawn places for object groups
					for (AActor* pActor : FoundPlaceObjectGroup)
					{
						// if id of spawn place is not current index continue
						if (((ALocationObjectGroup*)(pActor))->ID != i)
							continue;

						// spawn object group
						pObjGrp = GetWorld()->SpawnActor<ASingleObject>(objClass, pActor->GetActorLocation(), 
							pActor->GetActorRotation());
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
						// if current single object class not contains current object group object name continue
						if (!singleObjClass->GetName().Contains(objGrp.Objects[j].Name))
							continue;

						// check current object group actor children
						for (UActorComponent* pLocSingleObjComp : pObjGrp->GetComponentsByClass(ULocationSingleObjectComponent::StaticClass()))
						{
							// if index of current location not equals index of current object continue
							if (((ULocationSingleObjectComponent*)(pLocSingleObjComp))->ID != j)
								continue;

							// spawn object
							ASingleObject* pSingleObj = GetWorld()->SpawnActor<ASingleObject>(singleObjClass,
								((USceneComponent*)pLocSingleObjComp)->GetComponentLocation(),
								((USceneComponent*)pLocSingleObjComp)->GetComponentRotation());

							// check all questions
							for (FLessonObject lessonObj : Lessons->GetAllQuestions())
							{
								// if current question is not equal with current object question continue
								if (lessonObj.Name != objGrp.Objects[j].QuestionName)
									continue;

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

// set interaction reference
void APlayerPawn::SetInteraction(UInteraction* Interaction)
{
	// set interaction widget reference
	m_pInteraction = Interaction;

	// set percentage and image percentage
	m_pInteraction->SetPercentage(0.0f);
	m_pInteraction->SetImagePercentage();
}

// add lesson to list
void APlayerPawn::AddLessonClient_Implementation(FLesson _lesson)
{
	// if student add lesson to lessons component
	if (!m_isTeacher)
		Lessons->AddLesson(_lesson);
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
	TArray<AActor*> pFoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundPlayers);

	// check all players
	for (AActor* pPlayer : pFoundPlayers)
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
	TArray<AActor*> pFoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundPlayers);

	// check all players
	for (AActor* pPlayer : pFoundPlayers)
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

// disconnect student on clients
void APlayerPawn::DisconnectStudentClient_Implementation()
{
	// if not local player return
	if (!IsLocallyControlled())
		return;

	// get player controller
	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// if player controller valid disconnect from lesson
	if (pPlayerController)
	{
		// disconnect from server
		pPlayerController->ConsoleCommand(TEXT("disconnect"), true);

		// destroy session
		DestroySession();
	}
}
#pragma endregion

#pragma region public function
// add lesson to clients
void APlayerPawn::AddLessonToClients(FLesson _lesson)
{
	// add lesson to clients
	AddLessonClient(_lesson);
}

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

	// if server begin play server
	if (HasAuthority())
		BeginPlayServer();

	// if client begin play client
	else
		BeginPlayClient();
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

	// if server initialize student on server
	if (HasAuthority())
		return InitServerStudent();

	// client and local player and if student not initialized initialize student on client
	else if(!m_initStudent)
		return InitClientStudent();
	
	// client, local player and student initialized return true
	return true;
}

// initialize student on server
bool APlayerPawn::InitServerStudent()
{
	// if teacher
	if (m_isTeacher)
	{
		// if student has to be initialized
		if (m_initStudent)
			// show teacher component on clients
			ShowTeacherComponentsClient(Settings->GetName());

		// return true
		return true;
	}

	// not the teacher
	else
	{
		// get all player
		TArray<AActor*> pFoundPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundPlayers);

		// check all players
		for (AActor* pPlayer : pFoundPlayers)
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

// initialize student on client
bool APlayerPawn::InitClientStudent()
{
	// get all player
	TArray<AActor*> pFoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundPlayers);

	// if any player found
	if (!pFoundPlayers.Num())
		return false;

	// check all players
	for (AActor* pPlayer : pFoundPlayers)
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

// begin play on server
void APlayerPawn::BeginPlayServer()
{
	// if local player initialize lesson
	if (IsLocallyControlled())
	{
		// initialize lesson
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
	TArray<AActor*> pFoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundPlayers);

	// if player number less than 1 or 1 return
	if (pFoundPlayers.Num() <= 1)
		return;

	// degree for current player
	float degree = 0.0f;

	// if player count is between 2 and 5
	if (pFoundPlayers.Num() >= 2 && pFoundPlayers.Num() <= 5)
		// calculate degree for current player
		degree = ((pFoundPlayers.Num() - 2) % 4) * 90.0f;

	// if player count is between 6 and 9
	else if (pFoundPlayers.Num() >= 6 && pFoundPlayers.Num() <= 9)
		// calculate degree for current player
		degree = 45.0f + ((pFoundPlayers.Num() - 2) % 4) * 90.0f;

	// if player count is between 10 and 17
	else if (pFoundPlayers.Num() >= 10 && pFoundPlayers.Num() <= 17)
		// calculate degree for current player
		degree = 22.5f + ((pFoundPlayers.Num() - 2) % 8) * 45.0f;

	// if player count is between 18 and 33
	else if (pFoundPlayers.Num() >= 18 && pFoundPlayers.Num() <= 33)
		// calculate degree for current player
		degree = 11.25f + ((pFoundPlayers.Num() - 2) % 16) * 22.5f;

	// if player count is between 34 and 65
	else if (pFoundPlayers.Num() >= 34 && pFoundPlayers.Num() <= 65)
		// calculate degree for current player
		degree = 5.625f + ((pFoundPlayers.Num() - 2) % 32) * 11.25f;

	// location of teacher
	FVector location = FVector();

	// check all players
	for (AActor* pPlayer : pFoundPlayers)
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
	TArray<AActor*> pFoundObjects;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASingleObject::StaticClass(), pFoundObjects);

	// check all object
	for (AActor* pObj : pFoundObjects)
	{
		// set no collision for question widgets
		((ASingleObject*)pObj)->QuestionTeacher->SetCollisionProfileName("NoCollision");
		((ASingleObject*)pObj)->QuestionPractice->SetCollisionProfileName("NoCollision");
	}
}

// begin play on client
void APlayerPawn::BeginPlayClient()
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
	
	// target question base
	UQuestionBase* pTargetQuestionBase = nullptr;

	// save trace target to id (0 = no valid target, 1 = question widget target, 2 = single object target)
	int targetID = 0;

	// if trace target is 1
	if((targetID = GetTraceTargetID(hit, status)) == 1)
		// get question base
		pTargetQuestionBase = (UQuestionBase*)(((UWidgetComponent*)hit.GetComponent())->GetUserWidgetObject());

	// if target id valid
	if (targetID)
	{
		// decrease click timer
		DecreaseClickTimer(targetID, hit, status, pTargetQuestionBase);

		// if click timer lower than time to click return
		if (m_clickTimer >= ClickTime)
		{
			// if target id is question widget target click question widget
			if (targetID == 1)
				ClickQuestionWidget(hit);

			// if target is 3 click back menu widget
			else if (targetID == 3)
				ClickBackMenuWidget();

			// if target id is single object target and player status is not student click object
			else if (status != EPlayerStatus::STUDENT)
				ClickObject(hit, status);

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

// get trace target id from hit
int APlayerPawn::GetTraceTargetID(FHitResult _hit, EPlayerStatus _status)
{
	// if hit component valid and tag correct
	if (_hit.Component.IsValid() &&
		((_hit.Component->ComponentHasTag("QuestionPractice") && _status == EPlayerStatus::PRACTICE) ||
		(_hit.Component->ComponentHasTag("QuestionTeacher") && _status == EPlayerStatus::TEACHER) ||
			(_hit.Component->ComponentHasTag("QuestionStudent") && _status == EPlayerStatus::STUDENT)))
		// return target id 1
		return 1;

	// if hit actor valid and tag correct
	else if (_hit.Actor.IsValid() && _hit.Actor->ActorHasTag("LessonObject") && _status != EPlayerStatus::STUDENT)
		return 2;

	// if hit component valid and tag is menu widget
	else if (_hit.Component.IsValid() && _hit.Component->ComponentHasTag("MenuWidget"))
		return 3;

	// else return 0
	else
		return 0;
}

// increase or decrease click timer
void APlayerPawn::DecreaseClickTimer(int _targetID, FHitResult _hit, EPlayerStatus _status, UQuestionBase* _pQuesBase)
{
	// set trace target
	m_pTraceTarget = _hit.GetActor();

	// if target id is question widget target
	if (_targetID == 1)
		// release widget interaction click
		WidgetInteraction->ReleasePointerKey(FKey("LeftMouseButton"));

	// check clickable true
	if (_targetID == 1 && _pQuesBase != nullptr &&
		_pQuesBase->CheckClickable(((UWidgetComponent*)_hit.GetComponent())->GetDrawSize(),
			_hit.GetComponent()->GetComponentTransform(), _hit.Location, _status))
	{
		// increase click timer
		m_clickTimer += GetWorld()->GetDeltaSeconds();
	}

	// if trace target is object
	else if (_targetID == 2 || _targetID == 3)
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
}

// click on question widget
void APlayerPawn::ClickQuestionWidget(FHitResult _hit)
{
	// click widget interaction
	WidgetInteraction->PressPointerKey(FKey("LeftMouseButton"));

	// get question base from hit component
	UQuestionBase* pQuestionBase = (UQuestionBase*)(((UWidgetComponent*)(_hit.GetComponent()))->GetUserWidgetObject());

	// click at question base widget
	pQuestionBase->ClickOnWidget(((UWidgetComponent*)(_hit.GetComponent()))->GetDrawSize(),
		_hit.GetComponent()->GetComponentTransform(), _hit.Location);
}

// click on back to menu widget
void APlayerPawn::ClickBackMenuWidget()
{
	// get all players
	TArray<AActor*> pFoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundPlayers);

	// get lesson from teacher
	FLesson lesson = ((ULTVREGameInstance*)GetGameInstance())->GetCurrentLesson();

	// set creator of lesson to teacher name
	lesson.Creator = Settings->GetName();

	// check all players
	for (AActor* pPlayer : pFoundPlayers)
		// add lesson to clients
		((APlayerPawn*)pPlayer)->AddLessonToClients(lesson);

	// get player controller
	APlayerController* pPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// if player controller valid disconnect from lesson
	if (pPlayerController)
	{
		// if teacher
		if (m_isTeacher)
		{
			// check all players
			for (AActor* pPlayer : pFoundPlayers)
			{
				if (((APlayerPawn*)pPlayer) == this)
					continue;

				((APlayerPawn*)pPlayer)->DisconnectStudent();
			}
		}

		// timer to disconnect save
		float timer = 1.0f;

		// until only one player left of save timer under 0
		while (pFoundPlayers.Num() > 1 && timer > 0)
		{
			// get all players
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), pFoundPlayers);

			// decrease timer
			timer -= GetWorld()->GetDeltaSeconds();
		}

		// disconnect from server
		pPlayerController->ConsoleCommand(TEXT("disconnect"), true);

		// destroy session
		DestroySession();
	}
}

// click on single object
void APlayerPawn::ClickObject(FHitResult _hit, EPlayerStatus _status)
{
	// save widget component
	UWidgetComponent* pWidgetComp;

	// if player status is practice
	if (_status == EPlayerStatus::PRACTICE)
	{
		// widget component from question practice
		pWidgetComp = ((ASingleObject*)_hit.GetActor())->QuestionPractice;

		// if lesson is not answerable remove show hide question button
		if (((ULTVREGameInstance*)GetGameInstance())->GetCurrentLesson().Availability != ELessonAvailability::ANSWERABLE)
			((UQuestionBase*)(pWidgetComp->GetUserWidgetObject()))->RemoveQuestion();
	}

	// if player status is teacher
	else
	{
		// widget component from question teacher
		pWidgetComp = ((ASingleObject*)_hit.GetActor())->QuestionTeacher;
	}

	// toggle question widget
	pWidgetComp->ToggleVisibility();

	// if question widget visible set trace visible
	if (pWidgetComp->IsVisible())
		pWidgetComp->SetCollisionProfileName("TraceVisibility");

	// if question widget not visible set no trace
	else
		pWidgetComp->SetCollisionProfileName("NoCollision");
}
#pragma endregion