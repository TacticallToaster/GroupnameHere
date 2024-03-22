// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Core/HealthComponent.h"
#include "LlamaPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class CULTSHOOTER_API ALlamaPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* InPawn) override;

	UUserWidget* CurrentUI;
};
