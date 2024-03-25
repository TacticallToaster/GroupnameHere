// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Core/PlayerUI.h"
#include "Core/HealthComponent.h"
#include "Core/PlayerCharacter.h"
#include "LlamaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CULTSHOOTER_API ALlamaPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UFUNCTION()
	virtual void AcknowledgePossession(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UUserWidget* CurrentUI;
};
