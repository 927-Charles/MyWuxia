// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/BoxComponent.h"
#include "Components/InputComponent.h" 
#include "Components/SkeletalMeshComponent.h" 
#include "Components/CapsuleComponent.h"    

#include "GameFramework/PlayerController.h" 
#include "Animation/AnimMontage.h"
#include "UObject/ConstructorHelpers.h"
#include "Animation/AnimInstance.h"
#include "TimerManager.h"    // �������
#include "Engine/World.h"    // ȷ������ȷ��ȡ World


// Sets default values
ATopDownCharacter::ATopDownCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//�������ɱ۲����ø��ӽ�
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 1200.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false; // ���ü̳���ת�����̶ֹ��Ƕ�

	//���������
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);


	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	
}

// Called when the game starts or when spawned
void ATopDownCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATopDownCharacter::MoveForward(float Value)
{
	if (Value != 0.0f) {
		// ��ȡ���������ǰ���򣨸��ӽǵ� Y ��������
		const FVector CameraForward = CameraComponent->GetUpVector();
		const FVector Direction = FVector(CameraForward.X, CameraForward.Y, 0).GetSafeNormal();
		AddMovementInput(Direction, Value);

	}
}

void ATopDownCharacter::MoveLeft(float Value)
{
	if (Value != 0.0f) {
		// ������������ҷ��򣨸��ӽǵ� X ��������
		const FVector CameraRight = CameraComponent->GetRightVector();
		AddMovementInput(FVector(CameraRight.X, CameraRight.Y, 0).GetSafeNormal(), Value);
	}
}

void ATopDownCharacter::PrimaryAttack()
{
	if (!bIsAttacking) {
		bIsAttacking = true;
		// ���Ź�������
		PlayAttackAnimation();
		bIsAttacking = false;
	}	
}

void ATopDownCharacter::PlayAttackAnimation()
{
	if (AttackMontage) {
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance()) {
			AnimInstance->StopAllMontages(0.1f); // 0.1�뵭��ʱ��
		}
		float dur =PlayAnimMontage(AttackMontage,1);
		if (dur == 0) {
			UE_LOG(LogTemp, Warning, TEXT("Playing Montage dur: %d"), dur)
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Failed load Montage!"))
	}
}

void ATopDownCharacter::Dash()
{
	if (!bCanDash)return;
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		FHitResult HitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		if (HitResult.bBlockingHit) {
			FVector CurrentLocation = GetActorLocation();
			FVector TargetDirection_temp = (HitResult.Location - CurrentLocation);
			TargetDirection_temp.Z = 0;
			FVector TargetDirection = TargetDirection_temp.GetSafeNormal();
			FVector DashDestination = CurrentLocation + TargetDirection * DashDistance;
			UE_LOG(LogTemp, Error, TEXT("TargetDirection = %s"), *DashDestination.ToString());

			// ��ײ����ƶ�
			FHitResult SweepResult;
			bool bMoved = SetActorLocation(DashDestination, true, &SweepResult);
			if (!bMoved&&SweepResult.bBlockingHit) {
				DashDestination = CurrentLocation + TargetDirection * (DashDistance * SweepResult.Time);
				SetActorLocation(DashDestination, false);
			}
			// ��ȴ
			bCanDash = false;
			GetWorldTimerManager().SetTimer(
				DashCooldownTimerHandle,
				[this]() { bCanDash = true; },
				DashCooldown,
				false
			);

		}
	}
}

// Called every frame
void ATopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// �������½�ɫ�������λ��
	// ���ڷǹ���״̬�¸��³���
	if (!bIsAttacking)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult HitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
			if (HitResult.bBlockingHit)
			{
				const FVector Target = HitResult.Location;
				const FRotator LookAtRotation = (Target - GetActorLocation()).Rotation();
				SetActorRotation(FRotator(0, LookAtRotation.Yaw, 0));
			}
		}
	}
}

// Called to bind functionality to input
void ATopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// ��������
	PlayerInputComponent->BindAxis("MoveForward", this, &ATopDownCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveLeft", this, &ATopDownCharacter::MoveLeft);
	

	// �󶨶�������
	PlayerInputComponent->BindAction("PrimaryAttack", EInputEvent::IE_Pressed, this, &ATopDownCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_Pressed, this, &ATopDownCharacter::Dash);

}

