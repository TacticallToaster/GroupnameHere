// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "DrinkActor.generated.h"

UCLASS()
class CULTSHOOTER_API ADrinkActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrinkActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override; 

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Drink Mesh")
	class USkeletalMeshComponent* DrinkMesh;

	UPROPERTY()
	APlayerCharacter* Player;

	UPROPERTY()
	bool IsDrinkEmpty = false;



};
