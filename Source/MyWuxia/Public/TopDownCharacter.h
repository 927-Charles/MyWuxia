// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownCharacter.generated.h"

UCLASS()
class MYWUXIA_API ATopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATopDownCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//相机
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* CameraComponent;
	//弹簧臂
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmComponent;
	//攻击碰撞体检测
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Combat")
		class UBoxComponent* AttackCollision;
	// 普通攻击动画蒙太奇
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite,Category = "Combat")
		class UAnimMontage* AttackMontage;
	// 特殊攻击动画蒙太奇
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Combat")
		class UAnimMontage* AttackMontage2;
	// 是否正在攻击（用于锁定转向）
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
		bool bIsAttacking = false;
	UPROPERTY(EditAnyWhere, Category = "Dash")
		float DashDistance = 1000.0f;
	UPROPERTY(EditAnyWhere, Category = "Dash")
		float DashCooldown = 1.f;
	// 火球生成参数
	UPROPERTY(BlueprintReadWrite, Category = "Combat")
		TSubclassOf<class AFireBall> FireBallClass;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		float FireBallSpawnOffset = 100.0f; // 生成点偏移距离
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		float FireBallSpeed = 600.0f; // 火球飞行速度
	//角色属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float CurrentHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float CurrentMana = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float MaxMana = 50.0f;


	bool bCanDash = true;

	void MoveForward(float Value);
	void MoveLeft(float Value);
	void PrimaryAttack();
	void PlayAttackAnimation();
	void PlayAttackAnimation2();
	void Dash();
	void SpecialAttack();
	void TakeDamage(float DamageAmount);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	// 闪现冷却定时器句柄
	FTimerHandle DashCooldownTimerHandle;
};
