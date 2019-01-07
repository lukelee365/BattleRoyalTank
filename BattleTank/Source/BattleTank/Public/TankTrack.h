// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrick is used to set maximum driving force and to apply force to tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
private:
	float CurrentThrottle = 0;
	UTankTrack();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void ApplySidewayForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);	
	void DriveTrack();

public:
	//Max force per track in newton
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000000;
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	
};
