// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Core/PlayerUI.h"
#include "Core/LlamaSaveGame.h"
#include "Core/Mortal.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CULTSHOOTER_API APlayerCharacter : public ACharacter, public IMortal
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Die() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	ULlamaSaveGame* PlayerSaveData;
	UFUNCTION(BlueprintCallable, Category = "Save")
	void LoadPlayerData();
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SavePlayerData();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMeshComponent* MeshBody;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	float SensitivityX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	float SensitivityY;

	// Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputMapping")
	class UInputMappingContext* Imc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	class UInputAction* Wasd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	class UInputAction* JumpAction;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	class UInputAction* RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
	class UInputAction* LoadAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool IsSprinting;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float WalkingSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;


	UFUNCTION()
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump() override;
	void StartRunning();
	void StopRunning();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UPlayerUI> UIClass;
};
