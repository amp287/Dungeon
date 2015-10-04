// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Dungeon2GameMode.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON2_API ADungeon2GameMode : public AGameMode
{
	GENERATED_BODY()
public:

	ADungeon2GameMode();
	UPROPERTY(BlueprintReadOnly)
		TArray<TSubclassOf<class AItem>> ItemReferences;
	
	
};
