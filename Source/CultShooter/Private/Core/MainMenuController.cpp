// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MainMenuController.h"

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = (CreateWidget(this, MainMenuWidgetClass, "MainMenu"));
		MainMenuWidget->AddToViewport();
	}
}
