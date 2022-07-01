// Fill out your copyright notice in the Description page of Project Settings.


#include "..//SelfguidedMissiles/RocketProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"


// Sets default values
ARocketProjectile::ARocketProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCapsuleComponent"));
	SphereCollision->BodyInstance.SetCollisionProfileName("Projectile");
	SphereCollision->InitSphereRadius(32.0f);
	RootComponent = SphereCollision;  // Set root component.
	SphereCollision->OnComponentHit.AddDynamic(this, &ARocketProjectile::OnHit);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionProfileName("NoCollision");


	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(SphereCollision);
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
	ProjectileMovementComponent->MaxSpeed = 2000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ARocketProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARocketProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
void ARocketProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// Set Rocket Homing Props.
void ARocketProjectile::OnRocketHoming(UStaticMeshComponent* PTarget)
{
	if (IsValid(PTarget))
	{
		ProjectileMovementComponent->HomingTargetComponent = PTarget;
		ProjectileMovementComponent->bIsHomingProjectile = true;
		ProjectileMovementComponent->HomingAccelerationMagnitude = HommingAccMagnitude;
	}
}

// Rocket On Hit.
void ARocketProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EmitterTemplate, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());  // Spawn Explosion Emitter
	UGameplayStatics::SpawnSoundAtLocation(this, ExplosionSound, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());           // Spawn Explosion Sound

	if ((OtherActor != this) && (OtherActor != nullptr) && (OtherComp != nullptr))
	{
		if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}
		Destroy();
	}
}

