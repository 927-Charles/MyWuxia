// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPlayerController.h"
#include "TopDownCharacter.h"
#include "Blueprint/UserWidget.h"
#include "CombatPlayerController.h"


ACombatPlayerController::ACombatPlayerController() {
	// 硬编码加载 HUD 控件类（无需蓝图）
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDClassFinder(
		TEXT("/Game/Interface/WBP_HUD") // 替换为你的 WBP_HUD 实际路径
	);
	if (HUDClassFinder.Succeeded())
	{
		HUDWidgetClass = HUDClassFinder.Class;
	}
}
void ACombatPlayerController::BeginPlay() {
	Super::BeginPlay();

	SetViewTargetWithBlend(GetPawn(), 0.5f);
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	// 创建并显示 HUD
	if (HUDWidgetClass && GetWorld())
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}

