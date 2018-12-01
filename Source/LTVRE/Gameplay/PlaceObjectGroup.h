#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#pragma endregion

#pragma region project includes
#include "PlaceObjectGroup.generated.h"  
#pragma endregion

UCLASS()
/// <summary>
/// place where object groups can be spawned and placed
/// </summary>
class LTVRE_API APlaceObjectGroup : public AActor
{
	GENERATED_BODY()
	
public:	
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	APlaceObjectGroup()
	{
		// simple sphere component to see the object
		USphereComponent* pRoot = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
		RootComponent = pRoot;
	}
#pragma endregion

# pragma region UPROPERTY
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Place object group")
	/// <summary>
	/// id of place
	/// </summary>
	int ID;
# pragma endregion
};