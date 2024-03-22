// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/LlamaPlayerController.h"

void ALlamaPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//if (APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(Pawn))
	//{
	//	// Get the Player UI class from the PlayerCharacter
	//}
	if (UHealthComponent* HealthComponent = InPawn->GetComponentByClass<UHealthComponent>())
	{

	}
}
