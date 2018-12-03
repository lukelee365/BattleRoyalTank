// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	//Make super parent class Beginplay get called
	Super::BeginPlay();

	// Check in case of nullptr which may cause big problem
	if (auto tank = GetControlledTank()) {
		UE_LOG(LogTemp, Warning, TEXT("AI Control %s Begin Play"), *(tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Get Player Controller"));
	}

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



