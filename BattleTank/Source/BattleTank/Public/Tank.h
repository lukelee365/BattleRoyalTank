// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel; ///ForwardDeclaration. -> less dependency than Using #include.
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector HitLocation);
	//setter for the Barrel Object
	// A Function that can be called in blueprint
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTankReference(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Event)
	void Fire();

protected:
	UTankAimingComponent * TankAimingComponent = nullptr;

private:	
	// Sets default values for this pawn's properties
	ATank();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Referecne to spawn projectile
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 4000; //TODO Find sensible starting value of 1000 m/s

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditAnywhere, Category = Setup)
		float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
};
