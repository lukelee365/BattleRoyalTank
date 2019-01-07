// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

// DO not thing now
void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Get Called evey time when collide with other things
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewayForce();
	UE_LOG(LogTemp, Warning, TEXT("[ UTankTrack::OnHit] The value of throttle %f"), CurrentThrottle);
	// set the Throttle back to 0 so that stop
	CurrentThrottle = 0;
}


void UTankTrack::ApplySidewayForce()
{
	//Calculate the slippage speed
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto SlipageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAccelration = -SlipageSpeed / DeltaTime * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAccelration) / 2;
	TankRoot->AddForce(CorrectionForce);
	//Work ou t the require accelration to correct 
	//Calclate and apply side way Force
}


void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
