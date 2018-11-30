#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Paths.h"
#pragma endregion

/// <summary>
/// static helper class
/// </summary>
class LTVRE_API Helper
{
public:
#pragma region file path
	/// <summary>
	/// get absolute path with file name
	/// </summary>
	/// <param name="_fileName">file name</param>
	/// <returns>absolute path with file name</returns>
	static FString GetAbsoluteFileName(FString _fileName)
	{
		// if app is running on mobile
		bool mobile = true;

		// if not Android or IOS set mobile false
		if (!UGameplayStatics::GetPlatformName().Contains("Android") && !UGameplayStatics::GetPlatformName().Contains("IOS"))
			mobile = false;

		// file name to return
		FString fileName;

		// if mobile app
		if (mobile)
			// get save folder mobile
			fileName = "/storage/emulated/0/" + _fileName;

		// if not mobile app
		else
			// get save folder
			fileName = FPaths::ProjectSavedDir() + _fileName;

		// return absolute path file name
		return fileName;
	}
#pragma endregion

#pragma region settings
	/// <summary>
	/// convert settings struct to string in xml format
	/// </summary>
	/// <param name="_settings">settings to convert</param>
	/// <param name="_tabs">number of tabs</param>
	/// <returns>string in xml format</returns>
	static FString StructToStringXML(FPlayerSettings _settings, int _tabs = 0)
	{
		// string to return
		FString text = "";

		// name element
		text.Append(Element("Name", TCHAR_TO_ANSI(*_settings.Name), _tabs));

		// type element
		text.Append(Element("Type", TCHAR_TO_ANSI(*(FString::FromInt((int)_settings.Type))), _tabs));

		// sound element
		text.Append(Element("Sound", TCHAR_TO_ANSI(*(FString::FromInt(1 + (int)_settings.Sound / 20))), _tabs));

		// music element
		text.Append(Element("Music", TCHAR_TO_ANSI(*(FString::FromInt(1 + (int)_settings.Music / 20))), _tabs));

		// graphic element
		text.Append(Element("Graphic", TCHAR_TO_ANSI(*(FString::FromInt((int)_settings.Graphic))), _tabs));

		// return full string
		return text;
	}
#pragma endregion

#pragma region lesson
	/// <summary>
	/// convert lesson result struct to string in xml format
	/// </summary>
	/// <param name="_lessonResult">lesson result to convert</param>
	/// <param name="_tabs">number of tabs</param>
	/// <returns>string in xml format</returns>
	static FString StructToStringXML(FLessonResult _lessonResult, int _tabs = 0)
	{
		// string to return
		FString text = "";

		// name of lesson element
		text.Append(Element("Lesson", _lessonResult.m_LessonName, _tabs));

		// teacher name of lesson element
		text.Append(Element("Teacher", _lessonResult.m_TeacherName, _tabs));

		// date of lesson
		text.Append(Element("Date", _lessonResult.m_LessonDate, _tabs));

		// if questions available and at least one student
		if (_lessonResult.m_Questions.Num() > 0 && _lessonResult.m_Questions[0].m_StudentsAnswer.Num() > 0)
		{
			// question count
			int questionCount = _lessonResult.m_Questions.Num();

			// check all result student answers
			for (int i = 0; i < _lessonResult.m_Questions[0].m_StudentsAnswer.Num(); i++)
			{
				// add student result open element
				text.Append(OpenElement("StudentResult", _tabs));

				// add student name element
				text.Append(Element("Name", _lessonResult.m_Questions[0].m_StudentsAnswer[i].m_Name, _tabs + 1));

				// current student correct answer count
				int correctAnswers = 0;

				// check all questions
				for (FResultQuestion resQuestion : _lessonResult.m_Questions)
					// if first answer equal student answer increase correct answer count
					if (resQuestion.m_Question.Answers[0] == resQuestion.m_StudentsAnswer[i].m_GivenAnswer)
						correctAnswers++;

				// if correct answer higher than 0 calculate percentage and save in correct answer
				if (correctAnswers)
					correctAnswers = (int)(100.0f * correctAnswers / questionCount);

				// add percentage element
				text.Append(Element("Percentage", FString::FromInt(correctAnswers), _tabs + 1));

				// add student result close element
				text.Append(CloseElement("StudentResult", _tabs));
			}
		}

		// check all questions
		for (FResultQuestion resQuestion : _lessonResult.m_Questions)
		{
			// question open element
			text.Append(OpenElement("Question", _tabs));

			// get student count
			int studentCount = resQuestion.m_StudentsAnswer.Num();

			// number of correct answers
			int correctAnswers = 0;

			// check all result student answers
			for (FResultStudentAnswer resStudentAnswer : resQuestion.m_StudentsAnswer)
				// if answer given equal first answer increase correct answer count
				if (resQuestion.m_Question.Answers[0] == resStudentAnswer.m_GivenAnswer)
					correctAnswers++;

			// if correct answer higher than 0 calculate percentage and save in correct answer
			if (correctAnswers)
				correctAnswers = (int)(100.0f * correctAnswers / studentCount);

			// add percentage element
			text.Append(Element("Percentage", FString::FromInt(correctAnswers), _tabs + 1));

			// notice element
			text.Append(Element("Notice", resQuestion.m_Question.Notice, _tabs + 1));

			// question element
			text.Append(Element("Question", resQuestion.m_Question.Question, _tabs + 1));

			// check all answer
			for (int i = 0; i < resQuestion.m_Question.Answers.Num(); i++)
			{
				// element text
				FString elementText = FString("Answer").Append(FString::FromInt(i + 1)); ;

				// if first answer add correct to element
				if (i == 0)
					elementText.Append("(correct)");

				// add answer element
				text.Append(Element(elementText, resQuestion.m_Question.Answers[i], _tabs + 1));
			}

			// check all student answers
			for (FResultStudentAnswer resStudentAnswer : resQuestion.m_StudentsAnswer)
			{
				// student open element
				text.Append(OpenElement("Student", _tabs + 1));

				// student name element
				text.Append(Element("Name", resStudentAnswer.m_Name, _tabs + 2));

				// answer element
				text.Append(Element("Answer", resStudentAnswer.m_GivenAnswer, _tabs + 2));

				// student close element
				text.Append(CloseElement("Student", _tabs + 1));
			}

			// question close element
			text.Append(CloseElement("Question", _tabs));
		}

		// return full string
		return text;
	}

	/// <summary>
	/// convert lesson struct to string in xml format
	/// </summary>
	/// <param name="_lesson">lesson to convert</param>
	/// <param name="_tabs">number of tabs</param>
	/// <returns>string in xml format</returns>
	static FString StructToStringXML(FLesson _lesson, int _tabs = 0)
	{
		// string to return
		FString text = "";

		// lesson open element
		text.Append(OpenElement("Lesson", _tabs));

		// name of lesson element
		text.Append(Element("Name", _lesson.Name, _tabs + 1));

		// creator of lesson element
		text.Append(Element("Creator", _lesson.Creator, _tabs + 1));

		// availability of lesson element
		text.Append(Element("Availability", FString::FromInt((int)_lesson.Availability), _tabs + 1));

		// category of lesson element
		text.Append(Element("Category", FString::FromInt((int)_lesson.Category), _tabs + 1));

		// map open element
		text.Append(OpenElement("Map", _tabs + 1));

		// picture of map element
		text.Append(Element("Picture", _lesson.Map.Picture, _tabs + 2));

		// check all 2D transforms
		for (FVector2D vec2D : _lesson.Map.Transform2D)
		{
			// transform2d open element
			text.Append(OpenElement("Transform2D", _tabs + 2));

			// transform 2D x value element
			text.Append(Element("Transform2D.X", FString::FromInt(vec2D.X * 1000), _tabs + 3));

			// transform 2D y value element
			text.Append(Element("Transform2D.Y", FString::FromInt(vec2D.Y * 1000), _tabs + 3));

			// transform2d close element
			text.Append(CloseElement("Transform2D", _tabs + 2));
		}

		// check all object group names
		for (FString name : _lesson.Map.ObjectGroups)
			// name of object group element
			text.Append(Element("ObjectGroupName", name, _tabs + 2));

		// check all lesson object transforms
		for (FTransform transform : _lesson.Map.LessonObjectTransforms)
			// transform of object group
			StructToStringXML(transform, _tabs + 2);

		// check all lesson objects
		for (int i = 0; i < _lesson.Map.LessonObjectTransforms.Num(); i++)
		{
			// lesson object open element
			text.Append(OpenElement("LessonObject", _tabs + 2));

			// name of lesson object element
			text.Append(Element("Name", _lesson.Map.LessonObjectNames[i], _tabs + 3));

			// name of lesson object object name element
			text.Append(Element("ObjectName", _lesson.Map.LessonObjectObjectNames[i], _tabs + 3));

			// lesson object close element
			text.Append(CloseElement("LessonObject", _tabs + 2));
		}

		// map close element
		text.Append(CloseElement("Map", _tabs + 1));

		// lesson close element
		text.Append(CloseElement("Lesson", _tabs));

		// return full string
		return text;
	}

	/// <summary>
	/// convert lesson object group struct to string in xml format
	/// </summary>
	/// <param name="_lessonObjGrp">lesson object group to convert</param>
	/// <param name="_tabs">number of tabs</param>
	/// <returns>string in xml format</returns>
	static FString StructToStringXML(FLessonObjectGroup _lessonObjGrp, int _tabs = 0)
	{
		// string to return
		FString text = "";

		// object group open element
		text.Append(OpenElement("ObjectGroup", _tabs));

		// name of group object element
		text.Append(Element("Name", _lessonObjGrp.Name, _tabs + 1));

		// object name of group object element
		text.Append(Element("ObjectName", _lessonObjGrp.ObjectName, _tabs + 1));

		// check each 2D transform
		for (FVector2D vec2D : _lessonObjGrp.Transform2D)
		{
			// transform2d open element
			text.Append(OpenElement("Transform2D", _tabs + 1));

			// transform 2D x value element
			text.Append(Element("Transform2D.X", FString::FromInt(vec2D.X * 1000), _tabs + 2));

			// transform 2D y value element
			text.Append(Element("Transform2D.Y", FString::FromInt(vec2D.Y * 1000), _tabs + 2));

			// transform2d close element
			text.Append(CloseElement("Transform2D", _tabs + 1));
		}

		// check all lesson objects
		for (FObjectGroupObject lessonObj : _lessonObjGrp.Objects)
		{
			// lesson object open element
			text.Append(OpenElement("LessonObject", _tabs + 1));

			// name of group object element
			text.Append(Element("Name", lessonObj.Name, _tabs + 2));

			// question name of group object element
			text.Append(Element("QuestionName", lessonObj.QuestionName, _tabs + 2));

			// lesson object close element
			text.Append(CloseElement("LessonObject", _tabs + 1));
		}

		// object group close element
		text.Append(CloseElement("ObjectGroup", _tabs));

		// return full string
		return text;
	}

	/// <summary>
	/// convert lesson object struct to string in xml format
	/// </summary>
	/// <param name="_lessonObject">lesson object to convert</param>
	/// <param name="_tabs">number of tabs</param>
	/// <returns>string in xml format</returns>
	static FString StructToStringXML(FLessonObject _lessonObject, int _tabs = 0)
	{
		// string to return
		FString text = "";

		// lesson object open element
		text.Append(OpenElement("LessonObject", _tabs));

		// name of lesson object element
		text.Append(Element("Name", _lessonObject.Name, _tabs + 1));

		// object name of lesson object element
		text.Append(Element("ObjectName", _lessonObject.ObjectName, _tabs + 1));

		// notice of lesson object element
		text.Append(Element("Notice", _lessonObject.Notice, _tabs + 1));

		// question of lesson object element
		text.Append(Element("Question", _lessonObject.Question, _tabs + 1));

		// check all answers
		for (FString answer : _lessonObject.Answers)
			// answer of lesson object element
			text.Append(Element("Answer", answer, _tabs + 1));

		// lesson object close element
		text.Append(CloseElement("LessonObject", _tabs));

		// return full string
		return text;
	}

	/// <summary>
	/// convert transform struct to string in xml format
	/// </summary>
	/// <param name="_transform">transform to convert</param>
	/// <param name="_tabs">number of tabs</param>
	/// <returns>string in xml format</returns>
	static FString StructToStringXML(FTransform _transform, int _tabs = 0)
	{
		// string to return
		FString text = "";

		// transform open element
		text.Append(OpenElement("Transform", _tabs));

		// location of transform element
		text.Append(Element("Location.X", FString::FromInt(_transform.GetLocation().X * 1000), _tabs + 1));
		text.Append(Element("Location.Y", FString::FromInt(_transform.GetLocation().Y * 1000), _tabs + 1));
		text.Append(Element("Location.Y", FString::FromInt(_transform.GetLocation().Z * 1000), _tabs + 1));

		// rotation of transform element
		text.Append(Element("Rotation.X", FString::FromInt(_transform.GetRotation().X * 1000), _tabs + 1));
		text.Append(Element("Rotation.Y", FString::FromInt(_transform.GetRotation().Y * 1000), _tabs + 1));
		text.Append(Element("Rotation.Y", FString::FromInt(_transform.GetRotation().Z * 1000), _tabs + 1));

		// scale of transform element
		text.Append(Element("Scale.X", FString::FromInt(_transform.GetScale3D().X * 1000), _tabs + 1));
		text.Append(Element("Scale.Y", FString::FromInt(_transform.GetScale3D().Y * 1000), _tabs + 1));
		text.Append(Element("Scale.Y", FString::FromInt(_transform.GetScale3D().Z * 1000), _tabs + 1));

		// transform close element
		text.Append(CloseElement("Transform", _tabs));

		// return full string
		return text;
	}

	/// <summary>
	/// single xml element
	/// </summary>
	/// <param name="_name">element name</param>
	/// <param name="_value">element value</param>
	/// <param name="_tabs">number of tabs</param>
	/// <returns>element as string</returns>
	static FString Element(FString _name, FString _value, int _tabs = 0)
	{
		// string to return
		FString text = "";

		// append open element
		text.Append(Tabs(_tabs));
		text.Append("<");
		text.Append(_name);
		text.Append(">");

		// append element value
		text.Append(_value);

		// append close element
		text.Append("</");
		text.Append(_name);
		text.Append(">\n");

		// return full string
		return text;
	}

	/// <summary>
	/// xml open element
	/// </summary>
	/// <param name="_name">element name</param>
	/// <param name="_tabs">number of tabs</param>
	/// <returns>open element as string</returns>
	static FString OpenElement(FString _name, int _tabs = 0)
	{
		// string to return
		FString text = "";

		// append open element
		text.Append(Tabs(_tabs));
		text.Append("<");
		text.Append(_name);
		text.Append(">\n");

		// return full string
		return text;
	}

	/// <summary>
	/// xml close element
	/// </summary>
	/// <param name="_name">element name</param>
	/// <param name="_tabs">number of tabs</param>
	/// <returns>open element as string</returns>
	static FString CloseElement(FString _name, int _tabs = 0)
	{
		// string to return
		FString text = "";

		// append open element
		text.Append(Tabs(_tabs));
		text.Append("</");
		text.Append(_name);
		text.Append(">\n");

		// return full string
		return text;
	}

	/// <summary>
	/// tab string
	/// </summary>
	/// <param name="_count">number of tabs</param>
	/// <returns>string with tabs</returns>
	static FString Tabs(int _count)
	{
		// string to return
		FString text = "";

		// through number of tabs
		for (int i = 0; i < _count; i++)
			text.Append("    ");

		// return full string
		return text;
	}
#pragma endregion
};