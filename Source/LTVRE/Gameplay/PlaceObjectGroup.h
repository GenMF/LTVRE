#pragma once

// UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceObjectGroup.generated.h"

UCLASS()
/// <summary>
/// place where object groups can be spawned and placed
/// </summary>
class LTVRE_API APlaceObjectGroup : public AActor
{
	GENERATED_BODY()
	
public:	
	/// <summary>
	/// constructor
	/// </summary>
	APlaceObjectGroup();

# pragma region UPROPERTY
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Place object group")
	/// <summary>
	/// id of place
	/// </summary>
	int ID;
# pragma endregion
};