// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/BoxComponent.h"
#include "Components/InputComponent.h" 
#include "Components/SkeletalMeshComponent.h" // 包含 GetMesh() 的头文件
#include "Components/CapsuleComponent.h"     // 包含 GetCapsuleComponent() 的头文件

#include "GameFramework/PlayerController.h"  // 提供 APlayerController 的定义
// Sets default values
ATopDownCharacter::ATopDownCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//创建弹簧臂并设置俯视角
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 1200.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false; // 禁用继承旋转，保持固定角度

	//创建摄像机
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
		// 获取摄像机的正前方向（俯视角的 Y 轴正方向）
		const FVector CameraForward = CameraComponent->GetUpVector();
		const FVector Direction = FVector(CameraForward.X, CameraForward.Y, 0).GetSafeNormal();
		AddMovementInput(Direction, Value);

	}
}

void ATopDownCharacter::MoveLeft(float Value)
{
	if (Value != 0.0f) {
		// 基于摄像机的右方向（俯视角的 X 轴正方向）
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
	  // 持续更新角色朝向鼠标位置
	if (APlayerController* PC = Cast<APlayerController>(GetController())) {
		FHitResult HitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		if (HitResult.bBlockingHit) {
			// 计算看向目标的旋转
			const FVector Target = HitResult.Location;
			const FRotator LookAtRotation = (Target - GetActorLocation()).Rotation();
			// 仅保留Yaw轴
			SetActorRotation(FRotator(0, LookAtRotation.Yaw, 0));
		}
	}
}

// Called to bind functionality to input
void ATopDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 绑定轴输入
	PlayerInputComponent->BindAxis("MoveForward", this, &ATopDownCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveLeft", this, &ATopDownCharacter::MoveLeft);

	// 绑定动作输入
	//PlayerInputComponent->BindAction("普通攻击", EInputEvent::IE_Pressed, this, &ATopDownCharacter::PrimaryAttack);
}

