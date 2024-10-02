// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"

#include "Gun.h"
#include "ShooterCharacter.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxCollider;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	Particle->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	EndLocation = FVector(StartLocation.X, StartLocation.Y, StartLocation.Z + 30.f);
}

// Called every frame
void AAmmoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AnimateBox(DeltaTime);
	
	if (OverlappedActor)
	{
		AGun* OverlappedWeapon = OverlappedActor->GetActiveWeapon();
		if (OverlappedWeapon && OverlappedWeapon->IsA(AmmoType))
		{
			StoredAmmo = OverlappedWeapon->FillMagazine(StoredAmmo);
		}
		

		if(StoredAmmo == 0)
		{
			Destroy();
		}
	}
}

void AAmmoBox::AnimateBox(const float &DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	SetActorLocation(FMath::VInterpConstantTo(CurrentLocation, EndLocation, DeltaTime, 15.f));

	UE_LOG(LogTemp, Warning, TEXT("CurrentLoc: %s"), *CurrentLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("EndLoc: %s"), *EndLocation.ToString());
	if (CurrentLocation.Z == EndLocation.Z)
	{
		EndLocation = StartLocation;
		StartLocation = CurrentLocation;
	}

	AddActorLocalRotation(FRotator(0.0f, RotationRate * DeltaTime, 0.f), true);
}

void AAmmoBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	OverlappedActor = Cast<AShooterCharacter>(OtherActor);
	
}

void AAmmoBox::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor == OverlappedActor)
	{
		OverlappedActor = nullptr;
	}
}

