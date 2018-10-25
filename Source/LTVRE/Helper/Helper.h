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
		{
			// get save folder mobile
			fileName = "/storage/emulated/0/" + _fileName;
		}

		// if not mobile app
		else
		{
			// get save folder
			fileName = FPaths::ProjectSavedDir() + _fileName;
		}

		// return absolute path file name
		return fileName;
	}
#pragma endregion

#pragma region settings
	/// <summary>
	/// convert settings struct to string in xml format
	/// </summary>
	/// <param name="_settings">settings to convert</param>
	/// <returns>string in xml format</returns>
	static FString StructToStringXML(FPlayerSettings _settings)
	{
		// string to return
		FString text = "";

		// write name into string
		text.Append("<Name>");
		text.Append(TCHAR_TO_ANSI(*_settings.Name));
		text.Append("</Name>\n");

		// write type into string
		text.Append("<Type>");
		text.Append(TCHAR_TO_ANSI(*(FString::FromInt((int)_settings.Type))));
		text.Append("</Type>\n");

		// write sound into string
		text.Append("<Sound>");
		text.Append(TCHAR_TO_ANSI(*(FString::FromInt(1 + (int)_settings.Sound / 20))));
		text.Append("</Sound>\n");

		// write music into string
		text.Append("<Music>");
		text.Append(TCHAR_TO_ANSI(*(FString::FromInt(1 + (int)_settings.Music / 20))));
		text.Append("</Music>\n");

		// write graphic into string
		text.Append("<Graphic>");
		text.Append(TCHAR_TO_ANSI(*(FString::FromInt((int)_settings.Graphic))));
		text.Append("</Graphic>\n");

		// return full string
		return text;
	}
#pragma endregion

#pragma region lesson
	/// <summary>
	/// convert lesson struct to string in xml format
	/// </summary>
	/// <param name="_lesson">lesson to convert</param>
	/// <returns>string in xml format</returns>
	static FString StructToStringXML(FLesson _lesson)
	{
		// string to return
		FString text = "";

		// lesson element
		text.Append("<Lesson>\n");

		// name of lesson
		text.Append("<Name>");
		text.Append(_lesson.Name);
		text.Append("</Name>\n");

		// creator of lesson
		text.Append("<Creator>");
		text.Append(_lesson.Creator);
		text.Append("</Creator>\n");

		// availability of lesson
		text.Append("<Availability>");
		text.Append(FString::FromInt((int)_lesson.Availability));
		text.Append("</Availability>\n");

		// category of lesson
		text.Append("<Category>");
		text.Append(FString::FromInt((int)_lesson.Category));
		text.Append("</Category>\n");

		// map element
		text.Append("<Map>\n");

		// type of map
		text.Append("<Type>");
		text.Append(FString::FromInt((int)_lesson.Map.Map));
		text.Append("</Type>\n");

		// picture of map
		text.Append("<Picture>");
		text.Append(_lesson.Map.Picture);
		text.Append("</Picture>\n");

		// check all 2D transforms
		for (FVector2D vec2D : _lesson.Map.Transform2D)
		{
			// transform 2D x value
			text.Append("<Transform2D.X>");
			text.Append(FString::FromInt(vec2D.X * 1000));
			text.Append("</Transform2D.X>\n");

			// transform 2D y value
			text.Append("<Transform2D.Y>");
			text.Append(FString::FromInt(vec2D.Y * 1000));
			text.Append("</Transform2D.Y>\n");
		}

		// check all object group names
		for (FString name : _lesson.Map.ObjectGroups)
		{
			// name of object group
			text.Append("<ObjectGroupName>");
			text.Append(name);
			text.Append("</ObjectGroupName>\n");
		}

		// map close element
		text.Append("</Map>\n");

		// lesson close element
		text.Append("</Lesson>\n");

		// return full string
		return text;
	}

	/// <summary>
	/// convert lesson object group struct to string in xml format
	/// </summary>
	/// <param name="_lessonObjGrp">lesson object group to convert</param>
	/// <returns>string in xml format</returns>
	static FString StructToStringXML(FLessonObjectGroup _lessonObjGrp)
	{
		// string to return
		FString text = "";

		// object group element
		text.Append("<ObjectGroup>\n");

		// name of group object
		text.Append("<Name>");
		text.Append(_lessonObjGrp.Name);
		text.Append("</Name>\n");

		// object name of group object
		text.Append("<ObjectName>");
		text.Append(_lessonObjGrp.ObjectName);
		text.Append("</ObjectName>\n");

		// check each 2D transform
		for (FVector2D vec2D : _lessonObjGrp.Transform2D)
		{
			// transform 2D x value
			text.Append("<Transform2D.X>");
			text.Append(FString::FromInt(vec2D.X * 1000));
			text.Append("</Transform2D.X>\n");

			// transform 2D y value
			text.Append("<Transform2D.Y>");
			text.Append(FString::FromInt(vec2D.Y * 1000));
			text.Append("</Transform2D.Y>\n");
		}

		// check all lesson objects
		for (FObjectGroupObject lessonObj : _lessonObjGrp.Objects)
		{
			// lesson object element
			text.Append("<LessonObject>\n");

			// name of group object
			text.Append("<Name>");
			text.Append(lessonObj.Name);
			text.Append("</Name>\n");

			// transform
			text.Append(StructToStringXML(lessonObj.Transform));

			// lesson object close element
			text.Append("</LessonObject>\n");
		}

		// object group close element
		text.Append("</ObjectGroup>\n");

		// return full string
		return text;
	}

	/// <summary>
	/// convert transform struct to string in xml format
	/// </summary>
	/// <param name="_transform">transform to convert</param>
	/// <returns>string in xml format</returns>
	static FString StructToStringXML(FTransform _transform)
	{
		// string to return
		FString text = "";

		// transform element
		text.Append("<Transform>\n");

		// location of transform
		text.Append("<Location.X>");
		text.Append(FString::FromInt(_transform.GetLocation().X * 1000));
		text.Append("</Location.X>\n");
		text.Append("<Location.Y>");
		text.Append(FString::FromInt(_transform.GetLocation().Y * 1000));
		text.Append("</Location.Y>\n");
		text.Append("<Location.Z>");
		text.Append(FString::FromInt(_transform.GetLocation().Z * 1000));
		text.Append("</Location.Z>\n");

		// rotation of transform
		text.Append("<Rotation.X>");
		text.Append(FString::FromInt(_transform.GetRotation().X * 1000));
		text.Append("</Rotation.X>\n");
		text.Append("<Rotation.Y>");
		text.Append(FString::FromInt(_transform.GetRotation().Y * 1000));
		text.Append("</Rotation.Y>\n");
		text.Append("<Rotation.Z>");
		text.Append(FString::FromInt(_transform.GetRotation().Z * 1000));
		text.Append("</Rotation.Z>\n");

		// scale of transform
		text.Append("<Scale.X>");
		text.Append(FString::FromInt(_transform.GetScale3D().X * 1000));
		text.Append("</Scale.X>\n");
		text.Append("<Scale.Y>");
		text.Append(FString::FromInt(_transform.GetScale3D().Y * 1000));
		text.Append("</Scale.Y>\n");
		text.Append("<Scale.Z>");
		text.Append(FString::FromInt(_transform.GetScale3D().Z * 1000));
		text.Append("</Scale.Z>\n");

		// transform close element
		text.Append("</Transform>\n");

		// return full string
		return text;
	}
#pragma endregion

};
