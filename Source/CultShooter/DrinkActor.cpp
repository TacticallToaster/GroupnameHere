// Fill out your copyright notice in the Description page of Project Settings.


#include "DrinkActor.h"

// Sets default values
ADrinkActor::ADrinkActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADrinkActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrinkActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADrinkActor::Interact()
{
	IInteractInterface::Interact();

	if (IsDrinkEmpty)
	{

		Player->EnableShoot = true;

	}



}

