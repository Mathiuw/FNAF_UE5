// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Kismet/GameplayStatics.h"
#include "NightGameMode.h"

ADoor::ADoor()
{
	//Create Static Mesh Component
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));

	//Set up Root component
	RootComponent = DoorMesh;
}

void ADoor::Interact()
{
	//Open/Close Door
	SetDoorState(!IsClosed);

	//If NightGamemode Add or Remove Energy Usage Level
	if (ANightGameMode* GameMode = Cast<ANightGameMode>(UGameplayStatics::GetGameMode(GetWorld() ) ) )
	{
		if (!IsClosed)
		{
			//Add energy usage level
			GameMode->RemoveEnergyUsageLevel();
		}
		else
		{
			//Remove energy usage level
			GameMode->AddEnergyUsageLevel();
		}
	}

}

void ADoor::SetDoorState(bool state)
{
	DoorMesh->SetVisibility(state);

	IsClosed = state;

	if (GEngine)
	{
		if (!state)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Door OPENED"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Door CLOSED"));
		}
	}
}

bool ADoor::GetIsClosed()
{
	return IsClosed;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	SetDoorState(false);
}
