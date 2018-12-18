// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel; ///ForwardDeclaration. -> less dependency than Using #include.
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector HitLocation);
	//setter for the Barrel Object
	// A Function that can be called in blueprint
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

protected:
	UTankAimingComponent * TankAimingComponent = nullptr;
	//U means Inheirt from UObject A Means inherit form AActor
	UTankBarrel* BarrelComponent = nullptr;


private:	
	// Sets default values for this pawn's properties
	ATank();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000; //TODO Find sensible starting value of 1000 m/s
	
};
