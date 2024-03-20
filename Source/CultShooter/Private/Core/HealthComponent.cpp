// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::ModifyHealth(float HealthDelta)
{
	float ModifiedHealth = CurrentHealth + HealthDelta;
	if (HealthDelta > 0)
	{
		CurrentHealth = ModifiedHealth > MaxHealth ? MaxHealth : ModifiedHealth;
	}
	else if (!bGraceActive)
	{
		CurrentHealth = ModifiedHealth < 0 ? 0 : ModifiedHealth;
		if (CurrentHealth == 0)
		{
			Die();
		}
		else
		{
			bGraceActive = true;
			GetOwner()->GetWorldTimerManager().SetTimer(GraceTimer, this, &UHealthComponent::GraceCompleted, GracePeriod);
		}
	}
}

void UHealthComponent::GraceCompleted()
{
	bGraceActive = false;
	GetOwner()->GetWorldTimerManager().ClearTimer(GraceTimer);
}

void UHealthComponent::Die()
{
	GetOwner()->Destroy();
}

