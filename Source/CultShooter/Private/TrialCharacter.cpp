// Fill out your copyright notice in the Description page of Project Settings.


#include "TrialCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
ATrialCharacter::ATrialCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	jumping = false;
}

// Called when the game starts or when spawned
void ATrialCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ATrialCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(jumping)
	{
		Jump();
	}

}

// Called to bind functionality to input
void ATrialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ATrialCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ATrialCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ATrialCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ATrialCharacter::LookUp);
}



void ATrialCharacter::MoveForward(float Value)
{
	if (Controller && (Value != 0.f))
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATrialCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ATrialCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ATrialCharacter::MoveRight(float Value)
{
	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);

}
