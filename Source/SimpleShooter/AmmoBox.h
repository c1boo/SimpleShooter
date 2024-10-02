// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

class UBoxComponent;
class AGun;

UCLASS()
class SIMPLESHOOTER_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UParticleSystemComponent* Particle;
	
	UPROPERTY(EditAnywhere, Category="Config")
	float RotationRate = 180.f;

	UPROPERTY(EditAnywhere, Category="Config")
	TSubclassOf<AGun> AmmoType;
	
	UPROPERTY(EditAnywhere, Category="Features")
	int32 StoredAmmo = 32.f;

	FVector StartLocation;
	FVector EndLocation;

	UPROPERTY()
	class AShooterCharacter* OverlappedActor;

	void AnimateBox(const float &DeltaTime);
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
};
