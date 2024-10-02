// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherMissile.h"

#include "ShooterCharacter.h"
#include "Gun.h"
#include "Engine/DamageEvents.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALauncherMissile::ALauncherMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = Mesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->bAutoActivate = false;
	ProjectileMovement->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void ALauncherMissile::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &ALauncherMissile::OnProjectileHit);

	if (TrailParticles)
	{
		UGameplayStatics::SpawnEmitterAttached(TrailParticles, Mesh, NAME_None, FVector(ForceInit),
		                                       FRotator::ZeroRotator, FVector(3, 3, 3));
	}
	ProjectileMovement->Activate(true);
}

// Called every frame
void ALauncherMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALauncherMissile::Fire(float ProjectileSpeed)
{
	// Set the velocity for the projectile
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileSpeed;

	// Now activate the projectile movement
	ProjectileMovement->Activate();
}


void ALauncherMissile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	SpawnParticles(Hit);

	TArray<FOverlapResult> ActorsInsideRadius;
	FCollisionShape ExplosionRadius = FCollisionShape::MakeSphere(ImpactRadius);
	bool bHasHit = GetWorld()->OverlapMultiByChannel(ActorsInsideRadius,
		Hit.Location,
		OtherActor->GetActorRotation().Quaternion(),
		ECollisionChannel::ECC_GameTraceChannel1,
		ExplosionRadius);

	if (bHasHit)
	{
		AGun* DamageCauser = Cast<AGun>(GetOwner());
		if (!DamageCauser) return;

		AController* CauserController = DamageCauser->GetOwnerController();
		if (!CauserController) return;

		TArray<AShooterCharacter*> OverlappedEnemies;
		for (FOverlapResult OverlapResult : ActorsInsideRadius)
		{
			AShooterCharacter* Enemy = Cast<AShooterCharacter>(OverlapResult.GetActor());
			if (Enemy)
			{
				if (OverlappedEnemies.Contains(Enemy)) continue;

				FPointDamageEvent DamageEvent(Damage, Hit, -GetActorForwardVector(), nullptr);
				Enemy->TakeDamage(Damage, DamageEvent, CauserController, DamageCauser);
				OverlappedEnemies.Add(Enemy);
			}
		}
	}
	Destroy();
}

void ALauncherMissile::SpawnParticles(const FHitResult& Hit)
{
	if (ImpactParticles && ImpactSound)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			ImpactParticles,
			Hit.Location, FRotator::ZeroRotator, FVector(5.f, 5.f, 5.f));

		UGameplayStatics::PlaySoundAtLocation(
			this,
			ImpactSound,
			Hit.Location);
	}
}

