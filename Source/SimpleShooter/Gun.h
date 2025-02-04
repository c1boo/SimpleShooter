// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	virtual bool PullTrigger();

	AController* GetOwnerController() const;

	UFUNCTION(BlueprintPure)
	int32 GetMaxAmmo() const {return MaxAmmo;}
	UFUNCTION(BlueprintPure)
	int32 GetAmmo() const {return Ammo;}

	UFUNCTION()
	int32 FillMagazine(int32 NrOfAmmo);
	
protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactParticle;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	float BulletDistance = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere)
	int32 MaxAmmo = 30.f;

	UPROPERTY(VisibleInstanceOnly)
	int32 Ammo;
	
	
	bool GunTrace(FHitResult& HitResult, FVector &ShotDirection);
};
