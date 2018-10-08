#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"  
#pragma endregion

#pragma region project includes
#include "ObjectGroup.generated.h"
#pragma endregion

#pragma region forward decleration
class APlaceSingleObject;
#pragma endregion

UCLASS()
/// <summary>
/// class for object group
/// </summary>
class LTVRE_API AObjectGroup : public AActor
{
	GENERATED_BODY()
	
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	AObjectGroup();
#pragma endregion

#pragma region UFUNCTION
	UFUNCTION(BlueprintCallable, Category = "Object group")
	/// <summary>
	/// add a single place to list
	/// </summary>
	/// <param name="PlaceSingleObject">place single object to add</param>
	void AddPlaceSingleObject(APlaceSingleObject* PlaceSingleObject);
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get all places where a single object can be placed
	/// </summary>
	/// <returns>list with all places where a single object can be placed</returns>
	inline TArray<APlaceSingleObject*> GetSingleObjectPlaces()
	{
		return m_singleObjectPlaces;
	}
#pragma endregion

private:
#pragma region private variables
	/// <summary>
	/// array of places where single objects can be placed
	/// </summary>
	TArray<APlaceSingleObject*> m_singleObjectPlaces;
#pragma endregion
};