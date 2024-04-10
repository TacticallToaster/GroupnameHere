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

protected:
	UFUNCTION()
	void OnStartGameClicked();

	UPROPERTY(EditAnywhere)
	FName StartLevel;
};
