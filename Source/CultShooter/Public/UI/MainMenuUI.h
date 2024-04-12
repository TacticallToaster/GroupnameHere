// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class CULTSHOOTER_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditAnywhere, Category = "MainMenu", meta = (BindWidget))
	UButton* StartGameButton;
	UPROPERTY(EditAnywhere, Category = "MainMenu", meta = (BindWidget))
	UButton* OptionsButton;
	UPROPERTY(EditAnywhere, Category = "MainMenu", meta = (BindWidget))
	UButton* ControlsButton;
	UPROPERTY(EditAnywhere, Category = "MainMenu", meta = (BindWidget))
	UButton* EndGameButton;

protected:
	UFUNCTION()
	void OnStartGameClicked();

	UFUNCTION()
	void OnOptionsClicked();

	UFUNCTION()
	void OnControlsClicked();

	UFUNCTION()
	void OnEndGameClicked();

	UPROPERTY(EditAnywhere)
	FName StartLevel;
};
