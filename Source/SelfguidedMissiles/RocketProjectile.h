// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "RocketProjectile.generated.h"


UCLASS(config = Game)
class SELFGUIDEDMISSILES_API ARocketProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARocketProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
		float HommingAccMagnitude = 12000;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDirection);

	// Set Rocket Target
	void OnRocketHoming(UStaticMeshComponent* PTarget);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovementComponent;

	// Static mesh component.
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		UStaticMeshComponent* StaticMesh;

	// Capsule collision component.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		USphereComponent* SphereCollision;

	//ExplosionParticle
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* EmitterTemplate;

	// Explosion Sound
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
		class USoundBase* ExplosionSound;

	// Returns CollisionComp subobject 
	USphereComponent* GetCollisionComp() const { return SphereCollision; }

	// Returns ProjectileMovement subobject
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovementComponent; }
};
