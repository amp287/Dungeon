// Fill out your copyright notice in the Description page of Project Settings.

#include "Dungeon2.h"
#include "Dungeon2GameMode.h"

ADungeon2GameMode::ADungeon2GameMode()
{
	TArray<uint8> lines;
	FString filePath = "G:/Unreal Projects/Dungeon2/Content/Items/ItemList.txt";
	FFileHelper::LoadFileToArray(lines, *filePath);
}


