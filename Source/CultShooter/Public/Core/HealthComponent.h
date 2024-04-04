// Fill out your copyright notice in the Description page of Project Settings.
// Code written by Tommy Brekke

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ProgressBar.h"
#include "TimerManager.h"
#include "Engine/TimerHandle.h"
#include "Core/Mortal.h"
#include "HealthComponent.generated.h"



DECLARE_DELEGATE_OneParam(FDamageDelegate, float)
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CULTSHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ModifyHealth(float HealthDelta);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(float DamageToApply);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ResetHealth();
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Die();
	void AssignUI(UProgressBar* InHealthBar);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float GracePeriod = 1;
	bool bGraceActive = false;
	UFUNCTION()
	void GraceCompleted();
	FTimerHandle GraceTimer;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	UProgressBar* HealthBarWidget;
};
