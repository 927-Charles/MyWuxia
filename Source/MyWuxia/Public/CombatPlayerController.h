// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CombatPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYWUXIA_API ACombatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACombatPlayerController();
protected:
	virtual void BeginPlay() override;
	// HUD 控件类（在蓝图中赋值）
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
		UUserWidget* HUDWidget;
};
