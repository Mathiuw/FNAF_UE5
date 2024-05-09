// Fill out your copyright notice in the Description page of Project Settings.


#include "CorridorLight.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NightGameMode.h"
#include "ClikableBase.h"

ACorridorLight::ACorridorLight()
{
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("Point Light");

	RootComponent = PointLightComponent;
}

void ACorridorLight::SetLightState(bool state)
{
	PointLightComponent->SetVisibility(state);

	if (!PointLightComponent->IsVisible())
	{
		//Broadcast Light OFF event
		OnLightOFF.Broadcast();

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Corridor Light OFF"));
	}
	else
	{
		//Broadcast Light ON event
		OnLightON.Broadcast();

		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Corridor Light ON"));
	}
}

void ACorridorLight::BeginPlay()
{
	Super::BeginPlay();

	//Disable Light at start
	PointLightComponent->SetVisibility(false);

	if (ClikableInteractor)
	{
		ClikableInteractor->OnActorClicked.AddUniqueDynamic(this, &ACorridorLight::SetLightState);
		ClikableInteractor->OnActorReleased.AddUniqueDynamic(this, &ACorridorLight::SetLightState);
	}

	//Get gamemode acd cast to ANightGameMode class
	ANightGameMode* NightGameMode = Cast<ANightGameMode>(UGameplayStatics::GetGameMode(this));

	//Set power out event
	if (NightGameMode)
	{
		NightGameMode->OnPowerOut.AddUniqueDynamic(this, &ACorridorLight::OnPowerOutFunc);
	}
	
}

void ACorridorLight::OnPowerOutFunc()
{
	PointLightComponent->SetVisibility(false);
}
