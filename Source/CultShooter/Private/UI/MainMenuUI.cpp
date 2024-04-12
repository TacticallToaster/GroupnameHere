// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuUI.h"

void UMainMenuUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	StartGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuUI::OnStartGameClicked);
}

void UMainMenuUI::OnStartGameClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("You clicked start game, Congratulations!"));
	}
	if (true)
	{
		UGameplayStatics::OpenLevel(this, StartLevel);

	}
}
