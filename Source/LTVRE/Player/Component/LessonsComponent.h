#pragma once

#pragma region system includes
#include <fstream>
#pragma endregion

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#pragma endregion

#pragma region project includes
#include "Utility/Structs.h"
#include "Lesson/SingleObject.h"
#include "LessonsComponent.generated.h"
#pragma endregion

#pragma region usings
using namespace std;
#pragma endregion

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/// <summary>
/// lessons component
/// </summary>
class LTVRE_API ULessonsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	ULessonsComponent() {}
#pragma endregion

#pragma region UPROPERTY
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all textures for maps
	/// </summary>
	TArray<UTexture2D*> MapTextures;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all textures for single objects
	/// </summary>
	TArray<UTexture2D*> SingleObjectTextures;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all textures for object groups
	/// </summary>
	TArray<UTexture2D*> ObjectGroupTextures;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all single objects
	/// </summary>
	TArray<TSubclassOf<ASingleObject>> SingleObjectClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all basic object groups
	/// </summary>
	TArray<TSubclassOf<ASingleObject>> ObjectGroupClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all basic object groups, to identify the 2d transform for the buttons
	/// </summary>
	TArray<FLessonObjectGroup> ObjectGroupInformations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required")
	/// <summary>
	/// all basic maps, to identify the 2d transform for the buttons
	/// </summary>
	TArray<FLessonObjectGroup> MapInformations;
#pragma endregion

#pragma region UFUNCTION
	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get all lessons
	/// </summary>
	/// <returns>all lessons</returns>
	FORCEINLINE TArray<FLesson> GetAllLessons() { return m_lessons; }

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get current lesson
	/// </summary>
	/// <returns>current lesson</returns>
	FORCEINLINE FLesson GetCurrentLesson() { return m_currentLesson; }

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set current lesson
	/// </summary>
	/// <param name="Lesson">lesson to set</param>
	/// <param name="NewLesson">lesson is new</param>
	void SetCurrentLesson(FLesson Lesson, bool NewLesson);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// empty the current lesson to default
	/// </summary>
	void EmptyCurrentLesson();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set name of current lesson
	/// </summary>
	/// <param name="Name">name to set</param>
	/// <returns>name changed</returns>
	bool SetLessonName(FString Name);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set creator of current lesson
	/// </summary>
	/// <param name="Creator">creator to set</param>
	void SetLessonCreator(FString Creator);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set availability of current lesson
	/// </summary>
	/// <param name="Availability">availability to set</param>
	void SetLessonAvailability(ELessonAvailability Availability);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set category of current lesson
	/// </summary>
	/// <param name="Category">category to set</param>
	void SetLessonCategory(ELessonCategory Category);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set texture name of current lesson map texture
	/// </summary>
	/// <param name="TextureName"></param>
	void SetLessonMapPicture(FString TextureName);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set object name of current lesson map at index
	/// </summary>
	/// <param name="Index">index of object</param>
	/// <param name="ObjectName">name to set</param>
	void SetLessonMapObject(int Index, FString ObjectName);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// save current lesson to lessons list
	/// </summary>
	/// <param name="LessonIsNew">if current lesson is new</param>
	/// <param name="Index">index of current lesson</param>
	/// <returns>lesson saved</returns>
	bool SaveCurrentLesson(bool LessonIsNew, int Index);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// delete current lesson at index
	/// </summary>
	/// <param name="Index">index of current lesson</param>
	void DeleteCurrentLessonAtIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get all object groups
	/// </summary>
	/// <returns>all object groups</returns>
	FORCEINLINE TArray<FLessonObjectGroup> GetAllObjectGroups() { return m_objectGroups; }

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get current object group
	/// </summary>
	/// <returns>current object group</returns>
	FORCEINLINE FLessonObjectGroup GetCurrentObjectGroup() { return m_currentObjectGroup; }

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set current lesson object group
	/// </summary>
	/// <param name="ObjectGroup">object group to set</param>
	/// <param name="NewObjectGroup">object group is new</param>
	void SetCurrentObjectGroup(FLessonObjectGroup ObjectGroup, bool NewObjectGroup);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// empty the current object group to default
	/// </summary>
	void EmptyCurrentObjectGroup();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set name of current object group
	/// </summary>
	/// <param name="Name">name to set</param>
	/// <returns>name changed</returns>
	bool SetObjectGroupName(FString Name);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set object name of current object group
	/// </summary>
	/// <param name="Name">name to set</param>
	void SetObjectGroupObjectName(FString Name);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set object group object at index (ID)
	/// </summary>
	/// <param name="ID">index in array</param>
	/// <param name="LessonObjectName">lesson object name</param>
	void SetObjectGroupObject(int ID, FString LessonObjectName);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// save current object group to object group list
	/// </summary>
	/// <returns>object group saved</returns>
	bool SaveCurrentObjectGroup();

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// delete an object group at given index
	/// </summary>
	/// <param name="Index">index of object group</param>
	/// <returns>if object group deleted</returns>
	void DeleteObjectGroupAtIndex(int Index);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get all questions
	/// </summary>
	/// <returns>all questions</returns>
	FORCEINLINE TArray<FLessonObject> GetAllQuestions() { return m_questionCatalog; }

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// get current question
	/// </summary>
	/// <returns>current question</returns>
	FORCEINLINE FLessonObject GetCurrentQuestion() { return m_currentQuestion; }

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set current question
	/// </summary>
	/// <param name="Question">question to set</param>
	void SetCurrentQuestion(FLessonObject Question);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set notice of current question
	/// </summary>
	/// <param name="Notice">notice to set</param>
	/// <returns>question saved</returns>
	bool SetCurrentQuestionNotice(FString Notice);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set question o current question
	/// </summary>
	/// <param name="Question">question to set</param>
	/// <returns>question saved</returns>
	bool SetCurrentQuestionQuestion(FString Question);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// set answer at index of current question
	/// </summary>
	/// <param name="Index">index of answer</param>
	/// <param name="Answer">answer to set</param>
	/// <returns>question saved</returns>
	bool SetCurrentQuestionAnswer(int Index, FString Answer);

	UFUNCTION(BlueprintCallable, Category = "Lessons component")
	/// <summary>
	/// delete current question from array
	/// </summary>
	void DeleteCurrentQuestion();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// set lesson name of lesson result
	/// </summary>
	/// <param name="_name">name to set</param>
	inline void SetResultLessonName(FString _name) { m_lessonResult.m_LessonName = _name; }

	/// <summary>
	/// set start date and time of lesson
	/// </summary>
	/// <param name="_date">date as string to set</param>
	inline void SetResultLessonDate(FString _date) { m_lessonResult.m_LessonDate = _date; }

	/// <summary>
	/// set teacher name of result lesson
	/// </summary>
	/// <param name="_name">name of teacher to set</param>
	inline void SetResultLessonTeacher(FString _name) { m_lessonResult.m_TeacherName = _name; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// load Lessons.xml
	/// </summary>
	void LoadLessons();

	/// <summary>
	/// add lesson
	/// </summary>
	/// <param name="_lesson"></param>
	void AddLesson(FLesson _lesson);

	/// <summary>
	/// add question to result lesson
	/// </summary>
	/// <param name="_lessonObj">lesson object to add</param>
	void AddResultLessonQuestion(FLessonObject _lessonObj);

	/// <summary>
	/// add student to result lesson
	/// </summary>
	/// <param name="_name">name of student to add</param>
	void AddResultLessonStudent(FString _name);

	/// <summary>
	/// set given answer of student in result lesson
	/// </summary>
	/// <param name="_studentName">student name</param>
	/// <param name="_objName">object name</param>
	/// <param name="_answer">answer</param>
	void SetResultQuestionGivenAnswer(FString _studentName, FString _objName, FString _answer);

	/// <summary>
	/// save result of lesson
	/// </summary>
	void SaveLessonResult();
#pragma endregion

private:
# pragma region private variables
	/// <summary>
	/// current lesson
	/// </summary>
	FLesson m_currentLesson;

	/// <summary>
	/// current lesson name
	/// </summary>
	FString m_currentLessonName;

	/// <summary>
	/// lessons from this player
	/// </summary>
	TArray<FLesson> m_lessons;

	/// <summary>
	/// current object group
	/// </summary>
	FLessonObjectGroup m_currentObjectGroup;

	/// <summary>
	/// current object group name
	/// </summary>
	FString m_currentObjectGroupName;

	/// <summary>
	/// object groups created from player
	/// </summary>
	TArray<FLessonObjectGroup> m_objectGroups;

	/// <summary>
	/// all questions
	/// </summary>
	TArray<FLessonObject> m_questionCatalog;

	/// <summary>
	/// current question
	/// </summary>
	FLessonObject m_currentQuestion;

	/// <summary>
	/// lesson categories that player can edit
	/// </summary>
	TArray<ELessonCategory> m_categories;

	/// <summary>
	/// result of current lesson
	/// </summary>
	FLessonResult m_lessonResult;
# pragma endregion

#pragma region private function
	/// <summary>
	/// save lessons
	/// </summary>
	void SaveLesson();

	/// <summary>
	/// save current question to array
	/// </summary>
	/// <returns>question saved</returns>
	bool SaveCurrentQuestion();
#pragma endregion
};