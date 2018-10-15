#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#pragma endregion

#pragma region project includes
#include "LocationSingleObjectComponent.generated.h" 
#pragma endregion

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
/// <summary>
/// location where object can be placed in a object group
/// </summary>
class LTVRE_API ULocationSingleObjectComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:	
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	ULocationSingleObjectComponent();
#pragma endregion

#pragma region UPROPERTY
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "location single object component")
	/// <summary>
	/// id of location
	/// </summary>
	int ID;
#pragma endregion
};