// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * This class save the common base data. So that we can calculate the changes of the data after using skills, items or
 * level up.
 */
class MYWUXIA_API CharacterAttribute
{
public:
	CharacterAttribute();
	CharacterAttribute(bool RandomData);
	CharacterAttribute(const CharacterAttribute &InCharacterAttribute);
	CharacterAttribute(int InHealth, int InMagic, int InAttack, int InDefense, int InSpeed);
	~CharacterAttribute();

private:
	/* Base attribute */
	int Health = -1;
	int Magic = -1;
	int Attack = -1;
	int Defense = -1;
	int Speed = -1;
};
