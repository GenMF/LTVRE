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
};