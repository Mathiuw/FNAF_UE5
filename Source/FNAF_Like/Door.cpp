// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "ClikableBase.h"
#include "Kismet/GameplayStatics.h"
#include "NightGameMode.h"

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

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Door opened"));
	}
	else
	{
		OnDoorClose.Broadcast();

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Door closed"));
	}
}

bool ADoor::GetIsClosed() const
{
	return IsClosed;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);

	//Power out event setup
	if (ANightGameMode* NightGameMode = Cast<ANightGameMode>(GameMode))
	{
		NightGameMode->OnPowerOut.AddUniqueDynamic(this, &ADoor::OnPowerOutFunc);
	}

	//Clikable event setup
	if (ClikableInteractor)
	{
		ClikableInteractor->OnActorClicked.AddUniqueDynamic(this, &ADoor::SetDoorState);
	}
}

void ADoor::OnPowerOutFunc()
{
	SetDoorState(false);

}