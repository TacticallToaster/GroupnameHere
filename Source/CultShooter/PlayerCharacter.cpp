// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include  "Camera/CameraComponent.h"
#include "InputCoreTypes.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.f, 0.0f);
	GetCharacterMovement()->bIgnoreBaseRotation = true;


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;

	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 30.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;


	InteractionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Area"));
	InteractionArea->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(Imc, 0);
		}
	}

	InteractionArea->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBoxBeginOverlap);

	InteractionArea->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnBoxEndOverlap);

	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FString TheFloatStr = FString::SanitizeFloat(GetCharacterMovement()->MaxWalkSpeed);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *TheFloatStr);
	}

	//RotatePlayer();

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(Wasd, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Jump);

	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartRunning);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopRunning);

	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Dashing);

	EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interaction);
}


void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();


	if (Controller != nullptr)
	{
		const FRotator YawPlayerRotation = FRotator(0, GetControlRotation().Yaw, 0);

		const FVector ForwardBackwards = FRotationMatrix(YawPlayerRotation).GetUnitAxis(EAxis::Y);

		const FVector RightDirection = FRotationMatrix(YawPlayerRotation).GetUnitAxis(EAxis::X);


		AddMovementInput(ForwardBackwards, MoveInput.X);
		AddMovementInput(RightDirection, MoveInput.Y);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{

	const FVector2D LookInput = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookInput.X * SensitivityX);

		AddControllerPitchInput(LookInput.Y * SensitivityY);

	}

}

void APlayerCharacter::Jump()
{
	Super::Jump();
}

void APlayerCharacter::StartRunning()
{

	IsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::StopRunning()
{

	IsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void APlayerCharacter::Dashing()
{

	//if statement check if the player is moving can dash
	if (GetCharacterMovement()->Velocity != FVector::ZeroVector)
	{

		GetCharacterMovement()->BrakingFriction = 0.0f;
		const FVector ForwardDirection = GetActorRotation().Vector();
		LaunchCharacter(ForwardDirection * DashDistance, true, true);
	}
}

void APlayerCharacter::Interaction()
{

	if (Interact)
	{

		Interact->Interact();

	}

}

void APlayerCharacter::Shoot()
{
	if (EnableShoot)
	{

		//if (ProjectileSpawn)
		//{
		//	bIsShooting = true;

		//	UWorld* World = GetWorld();
		//	if (World != nullptr)
		//	{
		//		//This finds where the player in which way player is looking at.
		//		const APlayerController* PlayerController = Cast<APlayerController>(GetController());
		//		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

		//		//Get the rotation of the socket with the name SocketHeadShoot
		//		const FRotator SocketRotation = GetMesh()->GetSocketRotation("SocketHeadShoot");

		//		//Get the location of the socket with the name SocketHeadShoot and add the socket rotation plus the vector created earlier
		//		const FVector SocketLocation = GetMesh()->GetSocketLocation("SocketHeadShoot") + SocketRotation.RotateVector(GunTipOff);

		//		FActorSpawnParameters ActorSpawnParams;
		//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		//		ProjectileFired = GetWorld()->SpawnActor<AProjectileActor>(ProjectileSpawn, SocketLocation, SpawnRotation, ActorSpawnParams);



		//	}

		//}

	}

}

//void APlayerCharacter::IsShooting()
//{
//
//	FTimerHandle TimerHandlePlayerCamera;
//
//	//Delay's time for 5 seconds and calls the function StopShoot after 5 seconds when player stop shooting
//	GetWorld()->GetTimerManager().SetTimer(TimerHandlePlayerCamera, this, &APlayerCharacter::StopShoot, 5.0f, false);
//
//}

//void APlayerCharacter::PlayerRotate()
//{
//
//	if (bIsShooting)
//	{
//		//Cast to the player controller
//		const APlayerController* PlayerController = Cast<APlayerController>(GetController());
//
//		if (PlayerController->PlayerCameraManager)
//		{
//			//Get the camera rotation
//			FVector PlayerCameraRotation = PlayerController->PlayerCameraManager->GetCameraRotation().Vector();
//
//			//Stop Camera rotation to influence the rotation of the player in the Z axis
//			PlayerCameraRotation.Z = 0.0f;
//
//			// the player rotation is equal to the camera rotation
//			const FRotator PlayerRotation = PlayerCameraRotation.Rotation();
//
//			//Set the player Rotation to the camera rotation
//			SetActorRotation(PlayerRotation);
//		}
//
//
//	}
//
//}

//void APlayerCharacter::StopShoot()
//{
//
//	bIsShooting = false;
//
//}


void APlayerCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Interact = Cast<IInteractInterface>(OtherActor);


}

void APlayerCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

