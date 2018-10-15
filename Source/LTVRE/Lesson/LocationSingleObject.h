#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h" 
#pragma endregion

#pragma region project includes
#include "LocationSingleObject.generated.h" 
#pragma endregion

UCLASS()
/// <summary>
/// location where object can be placed in a object group
/// </summary>
class LTVRE_API ALocationSingleObject : public AActor
{
	GENERATED_BODY()
	
public:	
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	ALocationSingleObject();
#pragma endregion

#pragma region UPROPERTY
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Location single object")
	/// <summary>
	/// id of location
	/// </summary>
	int ID;
#pragma endregion
};