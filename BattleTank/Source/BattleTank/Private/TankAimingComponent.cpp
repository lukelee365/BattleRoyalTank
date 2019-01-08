// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/StaticMesh.h"
#include "TankBarrel.h" // include all the code with TankBarrel, It will include all the file and its dependecy class
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) return;
	BarrelComponent = BarrelToSet;
	TurretComponent = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	//Make blueprint Deritive class now the event get called, good pratice to do it all the time
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(LogTemp, Warning, TEXT("[UTankAimingComponent::TickComponent] The component is ticking"));
	if (AmmoLeft == 0)
	{
		FiringStatus = EFiringStatus::NOAMMO;
	} 
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringStatus = EFiringStatus::RELOADING;
	}
	else if(IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::AIMING;
	}
	else
	{
		FiringStatus = EFiringStatus::LOCK;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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
	auto RotateAmount = DeltaRotation.Yaw;
	if(FMath::Abs(RotateAmount) > 180) {
		RotateAmount = -RotateAmount;
	}
	TurretComponent->RotateTurret(RotateAmount);
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(BarrelComponent))return false;
	return !(BarrelComponent->GetForwardVector().Equals(AimDirection, 0.1));
}

EFiringStatus UTankAimingComponent::GetFireStatus() const
{
	return FiringStatus;
}

void UTankAimingComponent::Fire() {

	if (!ensure(BarrelComponent)) { return; }

	if (FiringStatus != EFiringStatus::RELOADING && AmmoLeft>0)
	{
		//Spawn the projectile in barrel socket
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			BarrelComponent->GetSocketLocation(FName("Muzzle")),
			BarrelComponent->GetSocketRotation(FName("Muzzle"))
			);
		LastFireTime = FPlatformTime::Seconds();
		if (!ensure(Projectile)) return;
		Projectile->LaunchProjectile(LaunchSpeed);
		UE_LOG(LogTemp, Warning, TEXT("[ATank::Fire] is Reloading"));
		AmmoLeft--;
	}
}


