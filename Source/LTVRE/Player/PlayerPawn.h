#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#pragma endregion

#pragma region project includes
#include "PlayerPawn.generated.h"  
#pragma endregion

#pragma region forward decleration
class UCameraComponent;
class USettingsComponent;
class ULessonsComponent;
class UWidgetInteractionComponent;
class UInteraction;
#pragma endregion

UCLASS()
/// <summary>
/// player
/// </summary>
class LTVRE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	APlayerPawn();
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="DeltaTime">time since last frame</param>
	virtual void Tick(float DeltaTime) override;
#pragma endregion

#pragma region UPROPERTY
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Pawn")
	/// <summary>
	/// camera component of player
	/// </summary>
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Pawn")
	/// <summary>
	/// widget interaction component of player
	/// </summary>
	UWidgetInteractionComponent* WidgetInteraction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Pawn")
	/// <summary>
	/// setting component of player
	/// </summary>
	USettingsComponent* Settings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Pawn")
	/// <summary>
	/// lessons component of player
	/// </summary>
	ULessonsComponent* Lessons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Pawn")
	/// <summary>
	/// time until click activate
	/// </summary>
	float ClickTime = 1.0f;
#pragma endregion

#pragma region UFUNCTION
	UFUNCTION(BlueprintCallable, Category = "Player Pawn")
	/// <summary>
	/// initialize lesson in vr level
	/// </summary>
	void InitializeLesson();

	UFUNCTION(BlueprintCallable, Category = "Player Pawn")
	/// <summary>
	/// set interaction reference
	/// </summary>
	void SetInteraction(UInteraction* Interaction);
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// time until click
	/// </summary>
	float m_clickTimer;
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// target from line trace
	/// </summary>
	AActor* m_pTraceTarget;

	/// <summary>
	/// interaction widget reference
	/// </summary>
	UInteraction* m_pInteraction;
#pragma endregion
};