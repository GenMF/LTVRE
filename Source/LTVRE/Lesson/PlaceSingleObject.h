#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h" 
#pragma endregion

#pragma region project includes
#include "PlaceSingleObject.generated.h" 
#pragma endregion

UCLASS()
/// <summary>
/// place where object can be placed in a object group
/// </summary>
class LTVRE_API APlaceSingleObject : public AActor
{
	GENERATED_BODY()
	
public:	
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	APlaceSingleObject();
#pragma endregion

#pragma region UPROPERTY
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Place single object")
	/// <summary>
	/// id of place
	/// </summary>
	int ID;
#pragma endregion
};