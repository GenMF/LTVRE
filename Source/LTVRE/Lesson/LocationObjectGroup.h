#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#pragma endregion

#pragma region project includes
#include "LocationObjectGroup.generated.h"  
#pragma endregion

UCLASS()
/// <summary>
/// location where object groups can be spawned and placed
/// </summary>
class LTVRE_API ALocationObjectGroup : public AActor
{
	GENERATED_BODY()
	
public:	
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	ALocationObjectGroup();
#pragma endregion

# pragma region UPROPERTY
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Location object group")
	/// <summary>
	/// id of location
	/// </summary>
	int ID;
# pragma endregion
};