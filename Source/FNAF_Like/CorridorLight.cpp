// Fill out your copyright notice in the Description page of Project Settings.


#include "CorridorLight.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NightGameMode.h"

ACorridorLight::ACorridorLight()
{
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("Point Light");

	RootComponent = PointLightComponent;
}

void ACorridorLight::Interact()
{
	SetLightState(!PointLightComponent->IsVisible());

	//If NightGamemode Add or Remove Energy Usage Level
	if (ANightGameMode* GameMode = Cast<ANightGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (!PointLightComponent->IsVisible())
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

void ACorridorLight::SetLightState(bool state)
{
	PointLightComponent->SetVisibility(state);

	if (GEngine)
	{
		if (!PointLightComponent->IsVisible())
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Corridor Light OFF"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Corridor Light ON"));
		}
	}

}

void ACorridorLight::BeginPlay()
{
	Super::BeginPlay();

	//Disable Light at start
	PointLightComponent->SetVisibility(false);

}
