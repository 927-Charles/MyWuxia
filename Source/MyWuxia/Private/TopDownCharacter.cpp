// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/BoxComponent.h"
#include "Components/InputComponent.h" 
#include "Components/SkeletalMeshComponent.h" // ���� GetMesh() ��ͷ�ļ�
#include "Components/CapsuleComponent.h"     // ���� GetCapsuleComponent() ��ͷ�ļ�

#include "GameFramework/PlayerController.h"  // �ṩ APlayerController �Ķ���
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
	
}

// Called every frame
void ATopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	  // �������½�ɫ�������λ��
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		FHitResult HitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		if (HitResult.bBlockingHit) {
			// ���㿴��Ŀ�����ת
			const FVector Target = HitResult.Location;
			const FRotator LookAtRotation = (Target - GetActorLocation()).Rotation();
			// ������Yaw��
			SetActorRotation(FRotator(0, LookAtRotation.Yaw, 0));
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
	//PlayerInputComponent->BindAction("��ͨ����", EInputEvent::IE_Pressed, this, &ATopDownCharacter::PrimaryAttack);
}

