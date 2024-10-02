// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Launcher.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ALauncher : public AGun
{
	GENERATED_BODY()

public:
	ALauncher();

	virtual void BeginPlay() override;

	virtual bool PullTrigger() override;


private:

	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALauncherMissile> MissileClass;
	
	UPROPERTY(EditAnywhere)
	float MissileSpeed = 3000.f;

	UPROPERTY(EditAnywhere)
	float ImpactRadius = 200.f;
};
