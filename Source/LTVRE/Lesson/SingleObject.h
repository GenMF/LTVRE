#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#pragma endregion

#pragma region project includes
#include "SingleObject.generated.h"  
#pragma endregion

UCLASS()
/// <summary>
/// class for a single lesson object
/// </summary>
class LTVRE_API ASingleObject : public AActor
{
	GENERATED_BODY()
	
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	ASingleObject();
#pragma endregion
};