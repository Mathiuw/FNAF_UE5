// Fill out your copyright notice in the Description page of Project Settings.


#include "CorridorLightBase.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NightGameModeBase.h"
#include "ClikableBase.h"

ACorridorLightBase::ACorridorLightBase()
{
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>("Point Light");
	RootComponent = PointLightComponent;
}

void ACorridorLightBase::SetLightON()
{
	// Broadcast Light ON event
	OnLightON.Broadcast();
	PointLightComponent->SetVisibility(true);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Corridor Light ON"));
}

void ACorridorLightBase::SetLightOFF()
{
	// Broadcast Light OFF event
	OnLightOFF.Broadcast();
	PointLightComponent->SetVisibility(false);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("Corridor Light OFF"));
}

void ACorridorLightBase::BeginPlay()
{
	Super::BeginPlay();

	// Disable Light at start
	PointLightComponent->SetVisibility(false);

	if (ClikableInteractor)
	{
		ClikableInteractor->OnActorClicked.AddDynamic(this, &ACorridorLightBase::SetLightON);
		ClikableInteractor->OnActorReleased.AddDynamic(this, &ACorridorLightBase::SetLightOFF);
	}
	
	// Set power out event
	if (ANightGameModeBase* NightGameMode = Cast<ANightGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		NightGameMode->OnPowerOut.AddUniqueDynamic(this, &ACorridorLightBase::OnPowerOutFunc);
	}
	
}

void ACorridorLightBase::OnPowerOutFunc()
{
	PointLightComponent->SetVisibility(false);
}
