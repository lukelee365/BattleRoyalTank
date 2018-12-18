// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //ForwardDeclaration. Any define the class so that compiler happy, not files copy
                   //-> less dependency than Using #include It will copy all the header files and its dependency
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation, float LaunchSpeed);
	void SetBarrelReference(UTankBarrel* BarrelToSet);

protected:
	UTankBarrel* BarrelComponent = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	//void MoveBarrelTowards(FVector AimDirection);

};
