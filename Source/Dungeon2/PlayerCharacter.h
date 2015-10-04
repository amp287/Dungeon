// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Item.h"
#include "MyUserWidget.h"
//#include "ItemStruct.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class DUNGEON2_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		TArray<FItemStruct> inventory;

	//Reference UMG Asset in editor(should be assigned in editor)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMyUserWidget> InventoryAssetReference;

	//player control ref
	APlayerController* PlayerController;

	//reference to Actor from BeginOverlap
	AActor* CollisionActor;

	USceneComponent* DropLocation;

	//Set to true when player presses button set to false when released
	bool bInteract;

	//sets if the player can move (set to false in menus)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanMove;

	//keep reference of active inventory 
	UMyUserWidget* InventoryUI;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		UBoxComponent* TriggerBox;

	//Input Functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

	//Input variables
	FVector CurrentVelocity;
	FRotator CurrentRotation;

	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//open Inventory
	void OpenInventory();

	//add Item to inventory->(OLD now in item class)delete the function
	UFUNCTION(BlueprintCallable, Category = Item)
		void AddItem(FItemStruct item);

	UFUNCTION(BlueprintCallable, Category = Item)
		int32 RemoveItem(int32 index);
	
	UFUNCTION()
		void TriggerBoxBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
									int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void TriggerBoxEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
									int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void SpawnItem(FString ItemName);

	//set bInteract to false
	void SetInteractF();

	//set bInteract to true
	void SetInteractT();
};
