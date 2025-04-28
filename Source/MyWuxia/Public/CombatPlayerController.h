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
	// HUD �ؼ��ࣨ����ͼ�и�ֵ��
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
		UUserWidget* HUDWidget;
};
