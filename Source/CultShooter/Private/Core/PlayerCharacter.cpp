// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputCoreTypes.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->DestroyComponent();
	GetMesh()->SetActive(false);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.f, 0.0f);
	GetCharacterMovement()->bIgnoreBaseRotation = true;

	MeshBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
	MeshBody->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;


	SensitivityX = 1.2f;
	SensitivityY = 0.8f;
	WalkingSpeed = 600.f;
	SprintSpeed = 800.f;
	IsSprinting = false;

	if (!PlayerSaveData)
	{
		PlayerSaveData = Cast<ULlamaSaveGame>(UGameplayStatics::CreateSaveGameObject(ULlamaSaveGame::StaticClass()));
	}
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
	
	if (!PlayerSaveData)
	{
		PlayerSaveData = Cast<ULlamaSaveGame>(UGameplayStatics::CreateSaveGameObject(ULlamaSaveGame::StaticClass()));
		PlayerSaveData = Cast<ULlamaSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("CurrentSave"), 0));
	}
	SavePlayerData();
}

void APlayerCharacter::SavePlayerData()
{
	if (PlayerSaveData && (GetActorLocation() - PlayerSaveData->PlayerLocation).Length() > 50)
	{
		PlayerSaveData->PlayerLocation = GetActorLocation();
		PlayerSaveData->PlayerRotation = GetActorRotation();
		if (UGameplayStatics::SaveGameToSlot(PlayerSaveData,TEXT("CurrentSave"),0))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, TEXT("Data saved ... "));
		}
	}
}

void APlayerCharacter::LoadPlayerData()
{
	if (PlayerSaveData)
	{
		SetActorLocation(PlayerSaveData->PlayerLocation);
		SetActorRotation(PlayerSaveData->PlayerRotation);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*const FString TheFloatStr = FString::SanitizeFloat(GetCharacterMovement()->MaxWalkSpeed);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *TheFloatStr);
	}*/

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

	EnhancedInputComponent->BindAction(LoadAction, ETriggerEvent::Started, this, &APlayerCharacter::LoadPlayerData);
}

void APlayerCharacter::Die()
{
	if (PlayerSaveData)
	{
		LoadPlayerData();
	}
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

