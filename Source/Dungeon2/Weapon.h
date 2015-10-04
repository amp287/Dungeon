// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sword,
	Hammer,
	Spear,
	Knife,
	Mace
};

UCLASS()
class DUNGEON2_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		float Damage;

	UPROPERTY(BlueprintReadWrite)
		EWeaponType WeaponType;

	AWeapon();
	
};