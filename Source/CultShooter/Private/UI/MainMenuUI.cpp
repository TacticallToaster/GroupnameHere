// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuUI.h"

void UMainMenuUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	StartGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUI::OnStartGameClicked);
	OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUI::OnOptionsClicked);
	ControlsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUI::OnControlsClicked);
	EndGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUI::OnEndGameClicked);
}

void UMainMenuUI::OnStartGameClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("You clicked start game, Congratulations!"));
	}
	
}

void UMainMenuUI::OnOptionsClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Turquoise, TEXT("You clicked Options, I always believed in you"));
	}
}

void UMainMenuUI::OnControlsClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("You have clicked Controls, was this a bad thing?"));
	}
}

void UMainMenuUI::OnEndGameClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("You clicked end game, Farewell!"));
	}
	
}
