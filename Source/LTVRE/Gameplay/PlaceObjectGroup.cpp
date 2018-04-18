// project includes
#include "PlaceObjectGroup.h"

// UE4 includes
#include "Components/SphereComponent.h"

// constructor
APlaceObjectGroup::APlaceObjectGroup()
{
	// simple sphere component to see the object
	USphereComponent* Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	RootComponent = Root;
}