// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorBase.h"
#include "ClikableBase.h"
#include "Kismet/GameplayStatics.h"
#include "NightGameModeBase.h"

ADoorBase::ADoorBase()
{
	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorFrameMesh;
}

void ADoorBase::Interact()
{
	ToggleDoorState();
}

void ADoorBase::ToggleDoorState()
{
	IsClosed = !IsClosed;

	if (!IsClosed)
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

bool ADoorBase::GetIsClosed() const
{
	return IsClosed;
}

void ADoorBase::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);

	//Power out event setup
	if (ANightGameModeBase* NightGameMode = Cast<ANightGameModeBase>(GameMode))
	{
		NightGameMode->OnPowerOut.AddUniqueDynamic(this, &ADoorBase::OnPowerOutFunc);
	}

	//Clikable event setup
	if (ClikableInteractor)
	{
		ClikableInteractor->OnActorClicked.AddUniqueDynamic(this, &ADoorBase::ToggleDoorState);
	}
}

void ADoorBase::OnPowerOutFunc()
{
	if (IsClosed)
	{
		ToggleDoorState();
	}
}