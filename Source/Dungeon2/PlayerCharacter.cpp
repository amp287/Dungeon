// Fill out your copyright notice in the Description page of Project Settings.

#include "Dungeon2.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bInteract = false;

	// Create a dummy root component we can attach things to
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	UCapsuleComponent* capsule = GetCapsuleComponent();
	RootComponent = capsule;
	//capsule->AttachTo(RootComponent);
	float offset = capsule->GetScaledCapsuleHalfHeight();
	//RootComponent->SetRelativeLocation(FVector(0.0f, 0.0f, offset));*/
	
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -offset));

	UCameraComponent* camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->AttachTo(RootComponent);
	camera->SetRelativeLocation(FVector(-200.0f, 0.0f, 150.0f));
	camera->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));

	DropLocation = CreateDefaultSubobject<USceneComponent>(TEXT("DropComponent"));

	DropLocation->AttachTo(RootComponent);

	DropLocation->SetRelativeLocation(FVector(150, 0, 50));

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->AttachTo(RootComponent);
	TriggerBox->bHiddenInGame = true;
	TriggerBox->bGenerateOverlapEvents = true;
	TriggerBox->SetRelativeLocation(FVector(60, 0, -offset));
	TriggerBox->SetBoxExtent(FVector(60, 60, 60));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::TriggerBoxBeginOverlap);

	UE_LOG(LogTemp, Warning, TEXT("Constructor Ran"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (InventoryAssetReference)//should be assigned in editor
	{
		InventoryUI = CreateWidget<UMyUserWidget>(GetWorld(), InventoryAssetReference);
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
	}	

	PlayerController = GetWorld()->GetFirstPlayerController();
	bCanMove = true;
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	SetActorRotation(CurrentRotation);
	FVector direction = GetActorForwardVector();
	FVector NewLocation = GetActorLocation() + (direction * (CurrentVelocity.X * DeltaTime));
	SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveX", this, &APlayerCharacter::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &APlayerCharacter::Move_YAxis);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::OpenInventory);
	InputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::SetInteractT);
	InputComponent->BindAction("Interact", IE_Released, this, &APlayerCharacter::SetInteractF);
	

}

void APlayerCharacter::Move_XAxis(float AxisValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::SanitizeFloat(AxisValue));
	if (bCanMove)
	{
		CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 500.0f;
		//PlayerController->
	}
}

void APlayerCharacter::Move_YAxis(float AxisValue)
{
	//CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 10.0f;
	if (bCanMove)
		CurrentRotation.Yaw += FMath::Clamp(AxisValue, -1.0f, 1.0f) * 1.5f;
}

void APlayerCharacter::OpenInventory()
{
	if (InventoryUI)
	{
		if (InventoryUI->GetIsVisible())
		{
			InventoryUI->RemoveFromParent();
			InventoryUI->SetVisibility(ESlateVisibility::Hidden);
			PlayerController->bShowMouseCursor = false;
			PlayerController->bEnableClickEvents = false;
			PlayerController->bEnableMouseOverEvents = false;
			bCanMove = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ADD TO VIEWPORT"));
			InventoryUI->AddToViewport();
			InventoryUI->SetVisibility(ESlateVisibility::Visible);
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true;
			PlayerController->bEnableMouseOverEvents = true;
			bCanMove = false;
		}
	}
}

void APlayerCharacter::AddItem(FItemStruct item)
{
	item.UniqueID = inventory.Num();
	inventory.Add(item);
}

int32 APlayerCharacter::RemoveItem(int32 index)
{
	if (index >= inventory.Num())
		return -1;

	//Shift ObjectIds down
	for (int i = index + 1; i < inventory.Num(); i++)
	{
		if (i >= inventory.Num())
			break;
		if ((i - 1) != 0)
			inventory[i].UniqueID = i - 1;
	}

	SpawnItem(inventory[index].BlueprintName);
	inventory.RemoveAt(index);

	CollisionActor = NULL;

	return 0;
}

void APlayerCharacter::TriggerBoxBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
							int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	CollisionActor = OtherActor;
	if (bInteract)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact2"));
		if (Cast<AItem>(OtherActor))
		{
			Cast<AItem>(OtherActor)->Pickup(this);
			UE_LOG(LogTemp, Warning, TEXT("PickedUp"));
		}
	}
}
void APlayerCharacter::TriggerBoxEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	CollisionActor = NULL;
}

void APlayerCharacter::SetInteractT()
{
	bInteract = true;
	
	if (CollisionActor)
	{
		if (Cast<AItem>(CollisionActor))
		{
			Cast<AItem>(CollisionActor)->Pickup(this);
			UE_LOG(LogTemp, Warning, TEXT("True"));
			CollisionActor = NULL;
		}
	}


}

void APlayerCharacter::SetInteractF()
{
	UE_LOG(LogTemp, Warning, TEXT("False"));
	bInteract = false;
}

void APlayerCharacter::SpawnItem(FString ItemName)
{
	UObject* ClassPackage = ANY_PACKAGE;
	UClass* item = FindObject<UClass>(ClassPackage, *ItemName);

	if (item != nullptr)
	{
		FActorSpawnParameters Params;
		const FVector location = GetActorLocation() + DropLocation->RelativeLocation;
		const FRotator rotate = FRotator(0, 0, 0);
		GetWorld()->SpawnActor(item, 
			&location, &rotate,Params);
	}
}


