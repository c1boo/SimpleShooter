// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"

#include "LauncherMissile.h"

ALauncher::ALauncher()
{
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh, TEXT("MuzzleFlashSocket"));
}

void ALauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ALauncher::PullTrigger()
{
	bool Success = Super::PullTrigger();
	if (!Success) return false;

	const FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	const FRotator Rotation = GetOwner()->GetInstigatorController()->GetControlRotation();
		
	ALauncherMissile* Missile = GetWorld()->SpawnActor<ALauncherMissile>(MissileClass, Location, Rotation);
	if (Missile)
	{
		Missile->SetOwner(this);
		Missile->Fire(MissileSpeed);
		Missile->SetDamage(Damage);
		Missile->SetImpactRadius(ImpactRadius);
	}
	
	return true;
}
