// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //ForwardDeclaration. Any define the class so that compiler happy, not files copy
                   //-> less dependency than Using #include It will copy all the header files and its dependency
class UTankTurret;

UENUM()
enum class EFiringStatus : uint8
{
	AIMING,
	LOCK,
	RELOADING
};

//Holds Barrel's Property, Calculate and Do the Aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Status")
		EFiringStatus FiringStatus = EFiringStatus::RELOADING;
	//void MoveBarrelTowards(FVector AimDirection);

private:
	UTankBarrel * BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
