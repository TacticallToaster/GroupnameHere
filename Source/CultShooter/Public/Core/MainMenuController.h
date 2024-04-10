// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/MainMenuUI.h"
#include "MainMenuController.generated.h"

/**
 * 
 */
UCLASS()
class CULTSHOOTER_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMainMenuUI> MainMenuWidgetClass;

	
	UUserWidget* MainMenuWidget;
};
