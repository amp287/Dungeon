// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemTag.h"
#include "ItemStruct.generated.h"


USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_USTRUCT_BODY();

	FItemStruct();

	//Name of Item
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ItemName;

	//use to find correct mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemMeshNumber;

	//use in loot generation/savegame item info
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemRarity;

	//use in loot generation/savegame item info
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemMagic;

	//Start at 0, used to keep track of items
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 UniqueID;

	//LevelRequired to use item
	UPROPERTY(BlueprintReadWrite)
		int32 LevelReq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Armor;

	//Object Reference Set in editor/children blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BlueprintName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EType type;
};
