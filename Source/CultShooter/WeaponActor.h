// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "WeaponActor.generated.h"

UCLASS()
class CULTSHOOTER_API AWeaponActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Sphere where if the player is in it will appear E to Interact message
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "SphereCollider")
	class USphereComponent* SphereCollider;

	//Mesh for the gun
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class USkeletalMeshComponent* Weapon;

	//Player reference
	UPROPERTY()
	APlayerCharacter* Player;



	/*
	 *Everything related on how to gun will work
	 * IMC and Inputs for the gun
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="WeaponSettings")
	class UInputMappingContext* FireImc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSettings")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun Tip")
	FVector GunTipOff;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsShooting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bPickup = false;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

	UFUNCTION()
	void RotatePlayer();
	void StopFiring();
	void IsShooting();


	UPROPERTY()
	class AActor* ProjectileFired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting thing")
	TSubclassOf<AActor> ProjectileSpawn;

	virtual void Interact_Implementation() override;

	UFUNCTION()
	void AttachToPlayer(APlayerCharacter* PlayerCharacter);
};
