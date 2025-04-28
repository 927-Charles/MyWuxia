// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"
#include "Engine/World.h"    // �������
#include "TimerManager.h"    // ��ʱ�����
// Sets default values
AFireBall::AFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 600.0f;
	ProjectileMovement->MaxSpeed = 600.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f; // ������
}

void AFireBall::StartDestroyTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
		DestroyTimerHandle,
		[this]() { Destroy(); },
		5.0f,
		false
	);
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	StartDestroyTimer();

}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

