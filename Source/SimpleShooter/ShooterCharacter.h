// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetPercentageHealth() const;

	UFUNCTION(BlueprintPure)
	AGun* GetActiveWeapon() const;
	
	void Shoot();
	
private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void LookUpController(float AxisValue);
	void LookRightController(float AxisValue);
	void ChangeWeapon(float AxisValue);
	
	UPROPERTY(EditAnywhere)
	float MouseSensitivity = 40.f;

	UPROPERTY(EditAnywhere)
	float ControllerSensitivity = 60.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AGun>> WeaponsClasses;
	
	TArray<AGun*> Weapons;
	int32 ActiveWeaponIndex;
	
	void EquipWeapon(AGun* GunToEquip);
	void HideGun(AGun* GunToHide);
};
