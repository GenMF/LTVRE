#pragma region project includes
#include "LocationSingleObject.h" 
#pragma endregion

#pragma region UE4 includes
#include "Components/SphereComponent.h"
#pragma endregion

#pragma region constructor
// constructor
ALocationSingleObject::ALocationSingleObject()
{
	// simple sphere component to see the object
	USphereComponent* Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	RootComponent = Root;
}
#pragma endregion