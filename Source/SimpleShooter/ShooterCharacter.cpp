// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include <string>

#include "Gun.h"
#include "SimpleShooterGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
	if (GetMesh())
	{
		GetMesh()->HideBoneByName(TEXT("weapon_r"), PBO_None);	
	}

	for (TSubclassOf<AGun> WeaponClass : WeaponsClasses)
	{
		AGun* Gun = GetWorld()->SpawnActor<AGun>(WeaponClass);
		if (!Gun) continue;
		
		Gun->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::KeepRelativeTransform,
			TEXT("WeaponSocket"));
		Gun->SetOwner(this);
		Gun->SetActorHiddenInGame(true);
		Gun->SetActorEnableCollision(false);
		Weapons.Add(Gun);
	}
	
	ActiveWeaponIndex = 0;
	if (!Weapons.IsEmpty())
	{
		EquipWeapon(Weapons[ActiveWeaponIndex]);	
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpController"), this,&AShooterCharacter::LookUpController);
	PlayerInputComponent->BindAxis(TEXT("LookRightController"), this,&AShooterCharacter::LookRightController);
	PlayerInputComponent->BindAxis(TEXT("ChangeWeapon"), this, &AShooterCharacter::ChangeWeapon);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed,this, &AShooterCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(-AxisValue * MouseSensitivity * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * MouseSensitivity * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookUpController(float AxisValue)
{
	AddControllerPitchInput(AxisValue * ControllerSensitivity * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightController(float AxisValue)
{
	AddControllerYawInput(AxisValue * ControllerSensitivity * GetWorld()->GetDeltaSeconds());
}


void AShooterCharacter::ChangeWeapon(float AxisValue)
{
	if (AxisValue == 0) return;

	HideGun(Weapons[ActiveWeaponIndex]);
	
	ActiveWeaponIndex = AxisValue > 0? ++ActiveWeaponIndex : --ActiveWeaponIndex;
	ActiveWeaponIndex = (ActiveWeaponIndex % Weapons.Num() + Weapons.Num()) % Weapons.Num();
	
	EquipWeapon(Weapons[ActiveWeaponIndex]);
}

void AShooterCharacter::EquipWeapon(AGun* GunToEquip)
{
	if (GunToEquip)
	{
		GunToEquip->SetActorHiddenInGame(false);
		GunToEquip->SetActorEnableCollision(true);
	}
}

void AShooterCharacter::HideGun(AGun* GunToHide)
{
	if (GunToHide)
	{
		GunToHide->SetActorHiddenInGame(true);
		GunToHide->SetActorEnableCollision(false);
	}
}


float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                    AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, FString::SanitizeFloat(DamageApplied));
	Health = FMath::Clamp(Health - DamageApplied, 0, MaxHealth);

	if(IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode)
		{
			GameMode->PawnKilled(this);
		}
		
		DetachFromControllerPendingDestroy();
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	return DamageApplied;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetPercentageHealth() const
{
	return Health / MaxHealth;
}

AGun* AShooterCharacter::GetActiveWeapon() const
{
	
	if (Weapons.Num() > ActiveWeaponIndex)
	{
		 return Weapons[ActiveWeaponIndex];
	}

	return nullptr;
}

void AShooterCharacter::Shoot()
{
	if (Weapons[ActiveWeaponIndex])
	{
		Weapons[ActiveWeaponIndex]->PullTrigger();
	}
} 

