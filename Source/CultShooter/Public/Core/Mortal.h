// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mortal.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UMortal : public UInterface
{
	GENERATED_BODY()
};

class IMortal
{
	GENERATED_BODY()

public:
	virtual void Die();
};
