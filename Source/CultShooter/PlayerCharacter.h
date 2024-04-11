// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InteractInterface.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CULTSHOOTER_API APlayerCharacter : public ACharacter
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

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	float SensitivityX = 1.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraMovement")
	float SensitivityY = 0.8f;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Dash Movement")
	class UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Input Interact")
	class UInputAction* InteractionAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DashDistance = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool IsSprinting = false;

	//Player walking speed
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float WalkingSpeed = 600.f;

	//The speed when player is sprinting
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float SprintSpeed = 800.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Interact")
	float InteractRange = 500.0f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Weapon")
	bool bHasWeapon = false;

	UFUNCTION(BlueprintCallable,Category = "Weapon")
	void SetHasWeapon(bool bHasNewWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetHasWeapon();

	bool EnableShoot = false;


	
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump() override;
	void StartRunning();
	void StopRunning();
	void Dashing();
	void Shoot();

	UFUNCTION(Category="Interact")
	void InteractWithObjects();
	





	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting thing")
	TSubclassOf<AActor> ProjectileSpawn;*/


};
