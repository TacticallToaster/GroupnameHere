// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/LlamaPlayerController.h"

void ALlamaPlayerController::AcknowledgePossession(APawn* InPawn)
{
	Super::AcknowledgePossession(InPawn);

	if (APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(InPawn))
	{
		// Get the Player UI class from the PlayerCharacter
		if (PlayerPawn->UIClass)
		{
			CurrentUI = CreateWidget(this, PlayerPawn->UIClass, "PlayerUI");
			CurrentUI->AddToViewport();
		}
	}
	if (UHealthComponent* HealthComponent = InPawn->GetComponentByClass<UHealthComponent>())
	{
		if (UPlayerUI* PlayerUI = Cast<UPlayerUI>(CurrentUI))
		{
			HealthComponent->AssignUI(PlayerUI->HealthBar);
		}
	}
}
