// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class CULTSHOOTER_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Health", meta = (BindWidget))
	UProgressBar* HealthBar;
};
