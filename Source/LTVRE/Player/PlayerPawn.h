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
class UTextRenderComponent;
class UInteraction;
class UQuestionBase;
class ASingleObject;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Pawn")
	/// <summary>
	/// static mesh component of player
	/// </summary>
	UStaticMeshComponent* HeadMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Pawn")
	/// <summary>
	/// widget interaction component of player
	/// </summary>
	UWidgetInteractionComponent* WidgetInteraction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Pawn")
	/// <summary>
	/// text render component of player name
	/// </summary>
	UTextRenderComponent* NameText;

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

	UFUNCTION(Server, Unreliable, WithValidation)
	/// <summary>
	/// set camera rotation on server
	/// </summary>
	/// <param name="_rotation">rotation to set</param>
	void SetCameraRotationServer(FRotator _rotation);

	UFUNCTION(NetMulticast, Unreliable)
	/// <summary>
	/// set camera rotation on client
	/// </summary>
	/// <param name="_rotation">rotation to set</param>
	void SetCameraRotationClient(FRotator _rotation);

	UFUNCTION(Server, Reliable, WithValidation)
	/// <summary>
	/// set name text on server
	/// </summary>
	/// <param name="_name">name to set</param>
	void SetNameTextServer(const FString &_name);
#pragma endregion

protected:
#pragma region protected override function
	/// <summary>
	/// called at begin play
	/// </summary>
	void BeginPlay() override;
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

#pragma region private function
	/// <summary>
	/// initialize question widget
	/// </summary>
	/// <param name="_pWidget">widget reference</param>
	/// <param name="_pSingleObj">single object reference</param>
	void InitWidget(UQuestionBase* _pWidget, ASingleObject* _pSingleObj);
#pragma endregion
};