#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interaction.generated.h" 
#pragma endregion

UCLASS()
/// <summary>
/// interaction widget
/// </summary>
class LTVRE_API UInteraction : public UUserWidget
{
	GENERATED_BODY()
	
public:
#pragma region UFUNCTION
	UFUNCTION(BlueprintCallable, Category = "Interaction widget")
	/// <summary>
	/// get percentage of click timer
	/// </summary>
	FORCEINLINE	float GetPercentage() { return m_percentage; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction widget")
	/// <summary>
	/// set image percentage
	/// </summary>
	void SetImagePercentage();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// set percentage
	/// </summary>
	/// <param name="_percentage">percentage to set</param>
	inline void SetPercentage(float _percentage) { m_percentage = _percentage; }
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// percentage of click timer
	/// </summary>
	float m_percentage;
#pragma endregion
};