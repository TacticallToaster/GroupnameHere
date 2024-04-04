// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LlamaSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CULTSHOOTER_API ULlamaSaveGame : public USaveGame
{
	GENERATED_BODY()
protected:
	ULlamaSaveGame();

public:
	UPROPERTY()
	FVector PlayerLocation;
	UPROPERTY()
	FRotator PlayerRotation;
};
