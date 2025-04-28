// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FireBall.generated.h"

UCLASS()
class MYWUXIA_API AFireBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBall();

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		UProjectileMovementComponent* ProjectileMovement;
	FTimerHandle DestroyTimerHandle;
	void StartDestroyTimer();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
