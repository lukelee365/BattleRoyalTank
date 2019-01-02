// Fill out your copyright notice in the Description page of Project Settings.
#include "TankBarrel.h"
#include "Tank.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	//UE_LOG(LogTemp, Warning, TEXT("[ UTankBarrel::Elevate] Relative Speed %f"), RelativeSpeed);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp(RawNewElevation, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
