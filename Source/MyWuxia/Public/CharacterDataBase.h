// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CharacterAttribute.h"
#include "ItemBase.h"

#include "CharacterDataBase.generated.h"

/**
 * This class is an abstract class that is the base class for player data or enermy data. Uses need to create
 * derived class for different data of every different character.
 */
UCLASS(abstract)
class MYWUXIA_API ACharacterDataBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterDataBase();

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
