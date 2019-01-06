// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"

void ATankPlayerController::BeginPlay() 
{
	//Make super parent class Beginplay get called
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if(ensure(AimingComponent))
		FoundAimiingComponent(AimingComponent);
	else
		UE_LOG(LogTemp, Warning, TEXT("[ATankPlayerController::BeginPlay] Cannot find aimming component"));

	// Check in case of nullptr which may cause big problem
	if (auto tank = GetControlledTank()) {
		UE_LOG(LogTemp, Warning, TEXT("[ATankPlayerController::BeginPlay] Player Control %s Begin Play"), *(tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATankPlayerController::BeginPlay] Cannot Get Player Controller"));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	auto Tank = GetControlledTank();
	///UE_LOG(LogTemp, Warning, TEXT("[ATankPlayerController::Tick] Tick is working"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto Tank = GetControlledTank();
	// check for null pointer
	if (!ensure(Tank)) { return; }
	//Get the Direction vector from crosshair and location, fire a lineTrace to detenind where hit on landScape

	FVector HitLocation;//Out Location

	if (GetSightRayHitLocation(HitLocation)) {
		Tank->AimAt(HitLocation);
	}


	//If hit Landscaoe
	//Tell Tank aim to the location

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation)const
{
	OutHitLocation = FVector(1.0f);
	//Find the Crosshiar Pos
	int32 ViewportSizeX, ViewportSizeY;
	//& mean it's an out parament which mean the passed value gona get changed
	//Get Screen Size
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location : %s"), *ScreenLocation.ToString());
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction : %s"), *LookDirection.ToString());
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		return true;
	}
	return false;
}

//Get the Look Direction from the Crosshair
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)const
{
	FHitResult HitResult;
	//Get Player Camera Location
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	FCollisionQueryParams CollisionParams;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	)) 
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		return false;
	}
 
}




