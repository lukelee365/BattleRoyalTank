// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //ForwardDeclaration. Any define the class so that compiler happy, not files copy
                   //-> less dependency than Using #include It will copy all the header files and its dependency
class UTankTurret;
//Holds Barrel's Property, Calculate and Do the Aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation, float LaunchSpeed);
	void SetTankReference(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
	UTankBarrel* BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	//void MoveBarrelTowards(FVector AimDirection);

};
