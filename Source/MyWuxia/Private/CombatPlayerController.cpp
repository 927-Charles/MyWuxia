// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPlayerController.h"
#include "TopDownCharacter.h"

void ACombatPlayerController::BeginPlay() {
	Super::BeginPlay();

	SetViewTargetWithBlend(GetPawn(), 0.5f);
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

}

