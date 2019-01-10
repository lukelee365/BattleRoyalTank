// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UTankProjectileMovementComponent;
UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
private:	
	// Sets default values for this actor's propertie
	UTankProjectileMovementComponent* ProjectileMovement = nullptr;
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	AProjectile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float Speed);
	
	
};
