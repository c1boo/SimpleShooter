// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool ARifle::PullTrigger()
{
	bool Success =Super::PullTrigger();

	if (!Success) return false;
			
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) return false;
		
	FHitResult HitResult;
	FVector ShotDirection;
	if (GunTrace(HitResult, ShotDirection))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, HitResult.ImpactPoint, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, HitResult.ImpactPoint, ShotDirection.Rotation());
		AActor* HitActor = HitResult.GetActor();
		if(HitActor)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this); 
		}
	}

	return true;
}



