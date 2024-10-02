// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LauncherMissile.generated.h"

UCLASS()
class SIMPLESHOOTER_API ALauncherMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALauncherMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire(float ProjectileSpeed);

	void SetDamage(float NewDamage) { Damage = NewDamage; }
	void SetImpactRadius(float NewRadius) { ImpactRadius = NewRadius; }
	
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* TrailParticles;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	float InitialSpeed = 1500.f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 1500.f;

	UPROPERTY(VisibleAnywhere)
	float ImpactRadius = 200.f;

	UPROPERTY(VisibleAnywhere)
	float Damage = 200.f;
	
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) ;

	void SpawnParticles(const FHitResult& Hit);
};
