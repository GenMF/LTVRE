#pragma region project includes
#include "PlaceSingleObject.h" 
#pragma endregion

#pragma region UE4 includes
#include "Components/SphereComponent.h"
#pragma endregion

#pragma region constructor
// constructor
APlaceSingleObject::APlaceSingleObject()
{
	// simple sphere component to see the object
	USphereComponent* Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	RootComponent = Root;
}
#pragma endregion