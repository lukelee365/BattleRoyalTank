// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"
/// Using the BlueprintSpawnableComponent will make this can be found in BluePrint
///Can Use UCLASS(meta = (BlueprintSpawnableComponent, hidecategories=("Collision"))) Hide Collision component to avoid other
///people break the program

///TankBarrel Component
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:// will get called by other class
	// -1 is max downwardspped, and =1 is upspeed
	void Elevate(float RelativeSpeed);	

private:
	//Sensible Default
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegree = 40;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegree = 0;
};
