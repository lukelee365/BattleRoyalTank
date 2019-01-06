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

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) return;
	BarrelComponent = BarrelToSet;
	TurretComponent = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(BarrelComponent)) { return; }
	FVector OutLaunchVelocity;
	auto StartLocation = BarrelComponent->GetSocketLocation("Muzzle");
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto OurTankName = GetOwner()->GetName();
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//Text in macro always use formated Text (BlaBlka : %s), *string
		//UE_LOG(LogTemp, Warning, TEXT("[UTankAimingComponent::AimAt] %s suggestd velocity is %s"), *OurTankName, *AimDirection.ToString());
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(BarrelComponent && TurretComponent)) return;
	auto AimRotation = AimDirection.Rotation();
	auto BarrelRotation = BarrelComponent->GetForwardVector().Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	BarrelComponent->Elevate(DeltaRotation.Pitch);
	TurretComponent->RotateTurret(DeltaRotation.Yaw);
}


