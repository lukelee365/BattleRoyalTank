// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/StaticMesh.h"
#include "TankBarrel.h" // include all the code with TankBarrel, It will include all the file and its dependecy class
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!BarrelComponent) { return; }
	FVector OutLaunchVelocity;
	auto StartLocation = BarrelComponent->GetSocketLocation("Muzzle");
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed)) {
		auto OurTankName = GetOwner()->GetName();
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		//Text in macro always use formated Text (BlaBlka : %s), *string
		UE_LOG(LogTemp, Warning, TEXT("[UTankAimingComponent::AimAt] %s suggestd velocity is %s"), *OurTankName, *AimDirection.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[UTankAimingComponent::AimAt] Cannot Calculate projectile velocity"));
	}


}
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	auto AimRotation = AimDirection.Rotation();
	auto BarrelRotation = BarrelComponent->GetForwardVector().Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	BarrelComponent->Elevate(DeltaRotation.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto AimRotation = AimDirection.Rotation();
	auto TurretRotation = TurretComponent->GetForwardVector().Rotation();
	auto DeltaRotation = AimRotation - TurretRotation;
	TurretComponent->RotateTurret(DeltaRotation.Yaw);
}

void UTankAimingComponent::SetTankReference(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	BarrelComponent = BarrelToSet;
	TurretComponent = TurretToSet;
}

