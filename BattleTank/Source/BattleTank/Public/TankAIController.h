// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class ATank;
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:	
	// means override the BeginPlay in parent
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// means function won't change anything
	ATank * GetControlledTank() const;

	ATank * GetPlayerControllerTank() const;
	//How close the radius is accept for stop
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 0;

	
};
