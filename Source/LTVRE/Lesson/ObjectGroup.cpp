#pragma region project includes
#include "ObjectGroup.h"  
#pragma endregion

#pragma region constructor
// constructor
AObjectGroup::AObjectGroup()
{

}
#pragma endregion

#pragma region UFUNCTION
// add a single place to list
void AObjectGroup::AddPlaceSingleObject(APlaceSingleObject* PlaceSingleObject)
{
	m_singleObjectPlaces.Add(PlaceSingleObject);
}
#pragma endregion