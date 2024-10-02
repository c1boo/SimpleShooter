// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(SceneComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Ammo = MaxAmmo;
}

bool AGun::PullTrigger()
{
	if (Ammo <= 0)
	{
		return false;
	}
	
	Ammo--;
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	return true;
}


bool AGun::GunTrace(FHitResult& HitResult, FVector &ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) return false;
	
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	FVector EndLocation = Location + Rotation.Vector() * BulletDistance;
	ShotDirection = -Rotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(HitResult, Location, EndLocation, ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return nullptr;

	return OwnerPawn->GetController();
}

int32 AGun::FillMagazine(int32 NrOfAmmo)
{
	const int32 FreeSlots = MaxAmmo - Ammo;
	const int32 UnfilledAmmo = FMath::Clamp(NrOfAmmo - FreeSlots, 0, NrOfAmmo);
	
	Ammo += NrOfAmmo - UnfilledAmmo;
	return UnfilledAmmo;	
}


