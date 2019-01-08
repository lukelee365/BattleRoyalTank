// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	//Make super parent class Beginplay get called
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ensure(ControlledTank))return;
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto Tank = GetControlledTank();
	auto PlayerTank = GetPlayerControllerTank();
	if (!ensure(Tank&&PlayerTank)) { return; }
	// Triger the AI tank to use A* to move, Call the RequestDirectMove in UNavMovementComponent and Everything Resawn it 
	MoveToActor(PlayerTank, AcceptanceRadius);
	// If Aiming or Lock then fire 
	AimingComponent->AimAt(GetPlayerControllerTank()->GetActorLocation());
	if(AimingComponent->GetFireStatus() == EFiringStatus::AIMING)
		AimingComponent->Fire();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControllerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


