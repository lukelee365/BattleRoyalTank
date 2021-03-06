// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class ATank;
class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank * GetControlledTank() const;
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimiingComponent(UTankAimingComponent* AimingCompRef);

private:
	UTankAimingComponent * AimingComponent = nullptr;
	// means override the BeginPlay in parent
	virtual void BeginPlay() override;
	// means override the Tick in parent Override mean check the parent do have the mehtod and Paramter
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnyWhere)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnyWhere)
		float CrossHairYLocation = 0.333333;
	UPROPERTY(EditAnyWhere)
		float LineTraceRange = 1000000.0; // in unreal 1 unit is 1cm

	//Statr the tank moving the barrel so that a shot would hit where the crosshair
	void AimTowardsCrosshair();
	// A constant function means that the variable in this class woun't be changed by this method
	// For this class it will be CrossHairXLocation and CrossHairYLocation
	// Variable in other method can be change
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation)const;
};
