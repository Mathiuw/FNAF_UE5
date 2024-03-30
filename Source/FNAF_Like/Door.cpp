// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "ClikableBase.h"

ADoor::ADoor()
{
	//Create Static Mesh Component
	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));

	//Set up Root component
	RootComponent = DoorFrameMesh;
}

void ADoor::Interact()
{
	//Open/Close Door
	SetDoorState(!IsClosed);

}

void ADoor::SetDoorState(bool state)
{
	IsClosed = state;

	if (!state)
	{
		OnDoorOpen.Broadcast();

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Door OPENED"));
	}
	else
	{
		OnDoorClose.Broadcast();

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Door CLOSED"));
	}
}

bool ADoor::IsDoorClosed() const
{
	return IsClosed;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	SetDoorState(false);

	if (ClikableInteractor)
	{
		ClikableInteractor->OnActorClicked.AddUniqueDynamic(this, &ADoor::SetDoorState);
	}
}
