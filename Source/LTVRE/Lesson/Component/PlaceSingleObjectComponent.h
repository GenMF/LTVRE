#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#pragma endregion

#pragma region project includes
#include "PlaceSingleObjectComponent.generated.h" 
#pragma endregion

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
/// <summary>
/// place where object can be placed in a object group
/// </summary>
class LTVRE_API UPlaceSingleObjectComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:	
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	UPlaceSingleObjectComponent();
#pragma endregion

#pragma region UPROPERTY
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Place single object")
	/// <summary>
	/// id of place
	/// </summary>
	int ID;
#pragma endregion
};