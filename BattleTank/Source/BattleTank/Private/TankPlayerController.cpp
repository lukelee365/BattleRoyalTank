// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() 
{
	//Make super parent class Beginplay get called
	Super::BeginPlay();

	// Check in case of nullptr which may cause big problem
	if (auto tank = GetControlledTank()) {
		UE_LOG(LogTemp, Warning, TEXT("[ATankPlayerController::BeginPlay] Player Control %s Begin Play"), *(tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATankPlayerController::BeginPlay] Cannot Get Player Controller"));
	}

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


