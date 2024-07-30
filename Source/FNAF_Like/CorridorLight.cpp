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

void ACorridorLight::SetLightON()
{
	//Broadcast Light ON event
	OnLightON.Broadcast();
	PointLightComponent->SetVisibility(true);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Corridor Light ON"));
}

void ACorridorLight::SetLightOFF()
{
	//Broadcast Light OFF event
	OnLightOFF.Broadcast();
	PointLightComponent->SetVisibility(false);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Corridor Light OFF"));
}

void ACorridorLight::BeginPlay()
{
	Super::BeginPlay();

	//Disable Light at start
	PointLightComponent->SetVisibility(false);

	if (ClikableInteractor)
	{
		ClikableInteractor->OnActorClicked.AddDynamic(this, &ACorridorLight::SetLightON);
		ClikableInteractor->OnActorReleased.AddDynamic(this, &ACorridorLight::SetLightOFF);
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
