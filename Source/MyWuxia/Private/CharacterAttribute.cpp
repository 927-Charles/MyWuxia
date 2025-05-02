// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttribute.h"

CharacterAttribute::CharacterAttribute()
{
}

CharacterAttribute::CharacterAttribute(bool RandomData)
{
	if (!RandomData)
	{
		// TODO(jin): random all the data if needed.
	}
}

CharacterAttribute::CharacterAttribute(const CharacterAttribute& InCharacterAttribute)
{
	this->Health = InCharacterAttribute.Health;
	this->Attack = InCharacterAttribute.Attack;
	this->Defense = InCharacterAttribute.Defense;
	this->Speed = InCharacterAttribute.Speed;
}

CharacterAttribute::CharacterAttribute(int InHealth, int InAttack, int InDefense, int InSpeed)
{
	this->Health = InHealth;
	this->Attack = InAttack;
	this->Defense = InDefense;
	this->Speed = InSpeed;
}

CharacterAttribute::~CharacterAttribute()
{
}
