// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"

#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollider->SetupAttachment(RootComponent);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(SphereCollider);

	GunTipOff = FVector(100.0f, 0, 0);

}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::Fire()
{
	if (ProjectileSpawn)
	{
		bIsShooting = true;

		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			//This finds where the player in which way player is looking at.
			const APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

			//Get the rotation of the socket with the name SocketHeadShoot
			const FRotator SocketRotation = Player->GetMesh()->GetSocketRotation("SocketHeadShoot");
			//Get the location of the socket with the name SocketHeadShoot and add the socket rotation plus the vector created earlier
			const FVector SocketLocation = Player->GetMesh()->GetSocketLocation("SocketHeadShoot") + SocketRotation.RotateVector(GunTipOff);

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			ProjectileFired = GetWorld()->SpawnActor<AActor>(ProjectileSpawn, SocketLocation, SpawnRotation, ActorSpawnParams);



		}
	}


}

void AWeaponActor::RotatePlayer()
{
	if (bIsShooting)
	{
		//Cast to the player controller
		const APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());

		if (PlayerController->PlayerCameraManager)
		{
			//Get the camera rotation
			FVector PlayerCameraRotation = PlayerController->PlayerCameraManager->GetCameraRotation().Vector();

			//Stop Camera rotation to influence the rotation of the player in the Z axis
			PlayerCameraRotation.Z = 0.0f;

			// the player rotation is equal to the camera rotation
			const FRotator PlayerRotation = PlayerCameraRotation.Rotation();

			//Set the player Rotation to the camera rotation
			Player->SetActorRotation(PlayerRotation);
		}



	}


	
}

void AWeaponActor::StopFiring()
{

	bIsShooting = false;
	

}

void AWeaponActor::IsShooting()
{

	FTimerHandle TimerHandlePlayerCamera;
	
		//Delay's time for 5 seconds and calls the function StopShoot after 5 seconds when player stop shooting
		GetWorld()->GetTimerManager().SetTimer(TimerHandlePlayerCamera, this, &AWeaponActor::StopFiring, 5.0f, false);


}

void AWeaponActor::Interact_Implementation()
{
	
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("Pick Up gun"));

	
	AttachToPlayer(Player);

}

void AWeaponActor::AttachToPlayer(APlayerCharacter* PlayerCharacter)
{
	Player = PlayerCharacter;

	

		if (Player == nullptr || Player->GetHasWeapon())
		{
			Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			return;

		}

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

		AttachToComponent(Player->GetMesh(), AttachmentRules, FName(TEXT("GunSocket")));
		Player->SetHasWeapon(true);
		SetOwner(Player);

		APlayerController* PlayerController = Cast<APlayerController>(Player->GetController());
		if (PlayerController)
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{

				Subsystem->AddMappingContext(FireImc, 1);

			}

			UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerController->InputComponent);

			if (EnhancedInputComponent)
			{

				EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AWeaponActor::Fire);
				EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AWeaponActor::IsShooting);

			}
		}

	
	


}

