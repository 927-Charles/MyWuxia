// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPlayerController.h"
#include "TopDownCharacter.h"
#include "Blueprint/UserWidget.h"
#include "CombatPlayerController.h"


ACombatPlayerController::ACombatPlayerController() {
	// Ӳ������� HUD �ؼ��ࣨ������ͼ��
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDClassFinder(
		TEXT("/Game/Interface/WBP_HUD") // �滻Ϊ��� WBP_HUD ʵ��·��
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
	// ��������ʾ HUD
	if (HUDWidgetClass && GetWorld())
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}

