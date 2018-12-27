// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	//Make super parent class Beginplay get called
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	// Check in case of nullptr which may cause big problem
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("[ATankAIController::BeginPlay] Controlled Tank %s found"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATankAIController::BeginPlay] Controlled Tank cannot be found"));
	}

	auto PlayerTank = GetPlayerControllerTank();
	// Check in case of nullptr which may cause big problem
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("[ ATankAIController::BeginPlay] Player control %s found"), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[ ATankAIController::BeginPlay] Cannot find player tank"));
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto Tank = GetControlledTank();
	if (!Tank) { return;}
	Tank->AimAt(GetPlayerControllerTank()->GetActorLocation());
	Tank->Fire();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControllerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


