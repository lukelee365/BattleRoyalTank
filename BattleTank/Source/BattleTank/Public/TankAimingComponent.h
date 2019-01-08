// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //ForwardDeclaration. Any define the class so that compiler happy, not files copy
                   //-> less dependency than Using #include It will copy all the header files and its dependency
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringStatus : uint8
{
	AIMING,
	LOCK,
	NOAMMO,
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
	void AimAt(FVector HitLocation);

	// A Function that can be called in blueprint
	UFUNCTION(BlueprintCallable, Category = "Event")
	void Fire();
	EFiringStatus GetFireStatus() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Status")
		EFiringStatus FiringStatus = EFiringStatus::RELOADING;
	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
		int AmmoLeft = 10;
	//void MoveBarrelTowards(FVector AimDirection);

private:
	UTankBarrel* BarrelComponent = nullptr;
	UTankTurret* TurretComponent = nullptr;
	FVector AimDirection = FVector::ZeroVector;
	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000; //TODO Find sensible starting value of 1000 m/s
	UPROPERTY(EditDefaultsOnly, Category = "Setup")//Every instance  must have same default value
		TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")//Every Instance must have same default value
		float ReloadTimeInSeconds = 3;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	bool IsBarrelMoving();
	
		//setter for the Barrel Object

	void MoveBarrelTowards(FVector AimDirection);
};
