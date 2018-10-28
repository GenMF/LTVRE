#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "XmlParser/Public/FastXml.h"
#pragma endregion

/// <summary>
/// file in xml format to lesson parser class
/// </summary>
class LTVRE_API FileToLessonParser : public IFastXmlCallback
{
public:
#pragma region public overrides
	/// <summary>
	/// get xml decleration
	/// </summary>
	/// <param name="ElementData">element data</param>
	/// <param name="XmlFileLineNumber">file line number</param>
	/// <returns>xml decleration correct processed</returns>
	virtual bool ProcessXmlDeclaration(const TCHAR * ElementData, int32 XmlFileLineNumber) override
	{
		return true;
	}

	/// <summary>
	/// get single xml element
	/// </summary>
	/// <param name="ElementName">element name</param>
	/// <param name="ElementData">element value</param>
	/// <param name="XmlFileLineNumber">file line number</param>
	/// <returns>xml element correct processed</returns>
	virtual bool ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override
	{
		// save element name in string
		FString name = ElementName;

		// if element is new set type
		if (m_currentType == "")
			m_currentType = name;

		// if element is lesson object
		if (name == "LessonObject")
		{
			// if current type is object group
			if (m_currentType == "ObjectGroup")
				m_currentType = "ObjectGroup_LessonObject";

			// if current type is lesson map
			else if (m_currentType == "Lesson_Map")
				m_currentType = "Lesson_Map_LessonObject";
		}

		// if element is object name
		else if (name == "ObjectName")
		{
			// if current type is lesson object
			if (m_currentType == "LessonObject")
				m_currentType = "LessonObject_ObjectName";
		}

		// if element is transform2d
		else if (name == "Transform2D")
		{
			// if current type is object group
			if (m_currentType == "ObjectGroup")
				m_currentType = "ObjectGroup_Transform2D";
		}

		// if element is map
		else if (name == "Map")
		{
			// set current type to lesson map
			m_currentType = "Lesson_Map";
		}

		// if element is name
		if (name == "Name")
		{
			// if current type is lesson set current lesson name
			if (m_currentType == "Lesson")
				m_currentLesson.Name = ElementData;

			// if current type is object group set current lesson object group name
			else if (m_currentType == "ObjectGroup")
				m_currentLessonObjectGroup.Name = ElementData;

			// if current type is lesson object set current lesson object name
			else if (m_currentType == "LessonObject")
				m_currentLessonObject.Name = ElementData;

			// if current type is object group set current lesson object group name
			else if (m_currentType == "ObjectGroup_LessonObject")
				m_currentObjectGroupObject.Name = ElementData;

			// if current type is lesson map add name to array
			else if (m_currentType == "Lesson_Map_LessonObject")
				m_currentLesson.Map.LessonObjectNames.Add(ElementData);
		}

		// if element is notice
		else if (name == "Notice")
		{
			// set notice of current lesson object
			m_currentLessonObject.Notice = ElementData;
		}

		// if element is question
		else if (name == "Question")
		{
			// set question of current lesson object
			m_currentLessonObject.Question = ElementData;
		}

		// if element is answer
		else if (name == "Answer")
		{
			// add answer of current lesson object
			m_currentLessonObject.Answers.Add(ElementData);
		}

		// if element is object name
		else if (name == "ObjectName")
		{
			// if current type is object group
			if (m_currentType == "ObjectGroup")
				// set object name of current object group
				m_currentLessonObjectGroup.ObjectName = ElementData;

			// if current type is lesson map add name to array
			else if (m_currentType == "Lesson_Map_LessonObject")
				m_currentLesson.Map.LessonObjectObjectNameNames.Add(ElementData);

			// if current type is not object group
			else
				// set object name of current lesson object
				m_currentLessonObject.ObjectName = ElementData;
		}

		// if element is transform2d.x
		else if (name == "Transform2D.X")
		{
			// set object group transform2d.x
			m_currentTransform2D.X = FCString::Atof(ElementData) * 0.001f;
		}

		// if element is transform2d.y
		else if (name == "Transform2D.Y")
		{
			// set object group transform2d.y
			m_currentTransform2D.Y = FCString::Atof(ElementData) * 0.001f;
		}

		// if element is question name
		else if (name == "QuestionName")
		{
			// set question name of current object group object
			m_currentObjectGroupObject.QuestionName = ElementData;
		}

		// if element is creator
		else if (name == "Creator")
		{
			// set creator of current lesson
			m_currentLesson.Creator = ElementData;
		}

		// if element is availability
		else if (name == "Availability")
		{
			// set availability of current lesson
			m_currentLesson.Availability = (ELessonAvailability)FCString::Atoi(ElementData);
		}

		// if element is category
		else if (name == "Category")
		{
			// set availability of current lesson
			m_currentLesson.Category = (ELessonCategory)FCString::Atoi(ElementData);
		}

		// if element is type
		else if (name == "Type")
		{
			// set type of current lesson map
			m_currentLesson.Map.Map = (ELessonMap)FCString::Atoi(ElementData);
		}

		// if element is picture
		else if (name == "Picture")
		{
			// set picture of current lesson map
			m_currentLesson.Map.Picture = ElementData;
		}

		// if element is object group name
		else if (name == "ObjectGroupName")
		{
			// add object group name to current lesson map
			m_currentLesson.Map.ObjectGroups.Add(ElementData);
		}

		// if element is location.x
		else if (name == "Location.X")
		{
			// get location of current lesson map transform
			FVector location = m_currentLessonMapTransform.GetLocation();

			// set location x of current lesson map transform
			location.X = FCString::Atof(ElementData) * 0.001f;

			// set location of current lesson map transform
			m_currentLessonMapTransform.SetLocation(location);
		}

		// if element is location.y
		else if (name == "Location.Y")
		{
			// get location of current lesson map transform
			FVector location = m_currentLessonMapTransform.GetLocation();

			// set location y of current lesson map transform
			location.Y = FCString::Atof(ElementData) * 0.001f;

			// set location of current lesson map transform
			m_currentLessonMapTransform.SetLocation(location);
		}

		// if element is location.z
		else if (name == "Location.Z")
		{
			// get location of current lesson map transform
			FVector location = m_currentLessonMapTransform.GetLocation();

			// set location z of current lesson map transform
			location.Z = FCString::Atof(ElementData) * 0.001f;

			// set location of current lesson map transform
			m_currentLessonMapTransform.SetLocation(location);
		}

		// if element is rotation.x
		else if (name == "Rotation.X")
		{
			// get rotation of current lesson map transform
			FQuat rotation = m_currentLessonMapTransform.GetRotation();

			// set rotation x of current lesson map transform
			rotation.X = FCString::Atof(ElementData) * 0.001f;

			// set rotation of current lesson map transform
			m_currentLessonMapTransform.SetRotation(rotation);
		}

		// if element is rotation.y
		else if (name == "Rotation.Y")
		{
			// get rotation of current lesson map transform
			FQuat rotation = m_currentLessonMapTransform.GetRotation();

			// set rotation y of current lesson map transform
			rotation.Y = FCString::Atof(ElementData) * 0.001f;

			// set rotation of current lesson map transform
			m_currentLessonMapTransform.SetRotation(rotation);
		}

		// if element is rotation.z
		else if (name == "Rotation.Z")
		{
			// get rotation of current lesson map transform
			FQuat rotation = m_currentLessonMapTransform.GetRotation();

			// set rotation z of current lesson map transform
			rotation.Z = FCString::Atof(ElementData) * 0.001f;

			// set rotation of current lesson map transform
			m_currentLessonMapTransform.SetRotation(rotation);
		}

		// if element is scale.x
		else if (name == "Scale.X")
		{
			// get scale of current lesson map transform
			FVector scale = m_currentLessonMapTransform.GetScale3D();

			// set scale x of current lesson map transform
			scale.X = FCString::Atof(ElementData) * 0.001f;

			// set scale of current lesson map transform
			m_currentLessonMapTransform.SetScale3D(scale);
		}

		// if element is scale.y
		else if (name == "Scale.Y")
		{
			// get scale of current lesson map transform
			FVector scale = m_currentLessonMapTransform.GetScale3D();

			// set scale y of current lesson map transform
			scale.Y = FCString::Atof(ElementData) * 0.001f;

			// set scale of current lesson map transform
			m_currentLessonMapTransform.SetScale3D(scale);
		}

		// if element is scale.z
		else if (name == "Scale.Z")
		{
			// get scale of current lesson map transform
			FVector scale = m_currentLessonMapTransform.GetScale3D();

			// set scale z of current lesson map transform
			scale.Z = FCString::Atof(ElementData) * 0.001f;

			// set scale of current lesson map transform
			m_currentLessonMapTransform.SetScale3D(scale);
		}

		// return true
		return true;
	}

	/// <summary>
	/// get single xml attribute
	/// </summary>
	/// <param name="AttributeName">attribute name</param>
	/// <param name="AttributeValue">attribute value</param>
	/// <returns>xml attribute correct processed</returns>
	virtual bool ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue) override
	{
		return true;
	}

	/// <summary>
	/// get if element scope ends
	/// </summary>
	/// <param name="Element">element</param>
	/// <returns>element scope ends</returns>
	virtual bool ProcessClose(const TCHAR* Element) override
	{
		// save element name in string
		FString name = Element;

		// lesson close element
		if (name == "Lesson")
		{
			// add current lesson to array
			m_Lessons.Add(m_currentLesson);

			// reset current lesson and type
			m_currentLesson = FLesson();
			m_currentType = "";
		}

		// object group close element
		else if (name == "ObjectGroup")
		{
			// if current type if object group
			if (m_currentType == "ObjectGroup")
			{
				// add current lesson object group to array
				m_LessonObjectGroups.Add(m_currentLessonObjectGroup);

				// reset current lesson and type
				m_currentLessonObjectGroup = FLessonObjectGroup();
				m_currentType = "";
			}
		}

		// lesson object close element
		else if (name == "LessonObject")
		{
			// if current type if lesson object
			if (m_currentType == "LessonObject")
			{
				// add current lesson object to array
				m_LessonObjects.Add(m_currentLessonObject);

				// reset current lesson object and type
				m_currentLessonObject = FLessonObject();
				m_currentType = "";
			}

			// if current type is not lesson object
			else
			{
				// add current lesson object to current object group
				m_currentLessonObjectGroup.Objects.Add(m_currentObjectGroupObject);

				// reset current object group object
				m_currentObjectGroupObject = FObjectGroupObject();

				// set current type back to lesson object
				m_currentType = "ObjectGroup";
			}
		}

		// object name close element
		else if (name == "ObjectName")
		{
			// if current type is object group object name
			if (m_currentType == "ObjectGroup_ObjectName")
				// set current type back to object group
				m_currentType = "ObjectGroup";

			// if current type is lesson object object name
			else if (m_currentType == "LessonObject_ObjectName")
				// set current type back to lesson object
				m_currentType = "LessonObject";
		}

		// transform2d close element
		else if (name == "Transform2D")
		{
			// if current type is object group
			if (m_currentType == "ObjectGroup_Transform2D")
			{
				// add current transform2d to current object group
				m_currentLessonObjectGroup.Transform2D.Add(m_currentTransform2D);

				// reset current transform2d
				m_currentTransform2D = FVector2D();

				// set current type back to object group
				m_currentType = "ObjectGroup";
			}

			// if current type is not object group
			else
			{
				// add current transform2d to current lesson map
				m_currentLesson.Map.Transform2D.Add(m_currentTransform2D);

				// reset current transform2d
				m_currentTransform2D = FVector2D();
			}
		}

		// transform close element
		else if (name == "Transform")
		{
			// add current transform to lesson map transforms
			m_currentLesson.Map.LessonObjectTransforms.Add(m_currentLessonMapTransform);

			// reset current transform
			m_currentLessonMapTransform = FTransform();
		}

		// return true
		return true;
	}

	/// <summary>
	/// get encountered comment
	/// </summary>
	/// <param name="Comment">comment</param>
	/// <returns>comment processed</returns>
	virtual bool ProcessComment(const TCHAR* Comment) override
	{
		return true;
	}
#pragma endregion

#pragma region public variables
	/// <summary>
	/// lesson object array
	/// </summary>
	TArray<FLessonObject> m_LessonObjects;

	/// <summary>
	/// lesson object group array
	/// </summary>
	TArray<FLessonObjectGroup> m_LessonObjectGroups;

	/// <summary>
	/// lesson array
	/// </summary>
	TArray<FLesson> m_Lessons;
#pragma endregion

private:
#pragma region private variables
	/// <summary>
	/// current lesson object
	/// </summary>
	FLessonObject m_currentLessonObject;

	/// <summary>
	/// current lesson object group
	/// </summary>
	FLessonObjectGroup m_currentLessonObjectGroup;

	/// <summary>
	/// current transform2d
	/// </summary>
	FVector2D m_currentTransform2D;
	
	/// /// <summary>
	/// current object group object
	/// </summary>
	FObjectGroupObject m_currentObjectGroupObject;

	/// <summary>
	/// current lesson map transform
	/// </summary>
	FTransform m_currentLessonMapTransform;

	/// <summary>
	/// current lesson
	/// </summary>
	FLesson m_currentLesson;

	/// <summary>
	/// current lesson type in xml
	/// </summary>
	FString m_currentType;
#pragma endregion
};