// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CharacterAttribute.h"

#include "ItemBase.generated.h"

UCLASS()
class MYWUXIA_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	CharacterAttribute BaseAttribute; /* The base attribute of this character */
	CharacterAttribute AddAttribute; /* The adding attribute to this character */
};
