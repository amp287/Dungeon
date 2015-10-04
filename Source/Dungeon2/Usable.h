// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "Usable.generated.h"

UINTERFACE(Blueprintable)
class UUsable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IUsable
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Use")
		void Pickup(class APlayerCharacter* Player);
};
