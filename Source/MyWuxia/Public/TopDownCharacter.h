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

	//Ïà»ú
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* CameraComponent;
	//µ¯»É±Û
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmComponent;
	//¹¥»÷Åö×²Ìå¼ì²â
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Combat")
		class UBoxComponent* AttackCollision;
	void MoveForward(float Value);
	void MoveLeft(float Value);
	void PrimaryAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
