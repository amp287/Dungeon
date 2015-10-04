// Fill out your copyright notice in the Description page of Project Settings.

#include "Dungeon2.h"
#include "Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ItemMesh->AttachTo(RootComponent);
	ItemMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	ItemStructInfo.ItemName = "Default";
	ItemStructInfo.ItemMagic = 0;
	ItemStructInfo.ItemMeshNumber = 0;
	ItemStructInfo.ItemRarity = 0;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AItem::Pickup(APlayerCharacter* Player)
{
	if (Player)
	{
		ItemStructInfo.UniqueID = Player->inventory.Num();
		Player->inventory.Add(ItemStructInfo);
	}

	Destroy();
}


