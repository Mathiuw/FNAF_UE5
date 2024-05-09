// Fill out your copyright notice in the Description page of Project Settings.


#include "NightGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Door.h"
#include "CorridorLight.h"
#include "SecurityCamera.h"
#include "GuardController.h"

void ANightGameMode::PowerConsume()
{
	Energy--;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Power depleted"));

	if (Energy <= 0)
	{
		//Send to all listners that power is out
		OnPowerOut.Broadcast();
		//TODO: finish timer implementation
	}
}

void ANightGameMode::AdvanceHour()
{ 
	if (Hour == 12)
	{
		Hour = 1;
		return;
	}

	Hour++;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, TEXT("Advanced hour"));

	if (Hour == 6)
	{
		//Send to all listners that night ended
		OnNightEnd.Broadcast();	
	}
}

void ANightGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Set energy to max
	Energy = MaxEnergy;

	//Night end events
	OnNightEnd.AddUniqueDynamic(this, &ANightGameMode::OnNightEndFunc);
	//Power out events
	OnPowerOut.AddUniqueDynamic(this, &ANightGameMode::OnPowerOutFunc);

	//Get player controller and check if it is AGuardController class
	AGuardController* GuardController = Cast<AGuardController>(UGameplayStatics::GetPlayerController(this, 0));

	//Get all cameras and send to the AGuardController
	if (GuardController)
	{
		TArray<AActor*> Cameras;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASecurityCamera::StaticClass(), Cameras);

		for (int i = 0; i < Cameras.Num(); i++)
		{
			//Camera cast
			ASecurityCamera* Camera = Cast<ASecurityCamera>(Cameras[i]);

			if (Camera)
			{
				GuardController->AddSecurityCamera(Camera);
			}
			else
			{
				//Add failed
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Failed to add camera"));
			}
		}
	}

	//Set door events
	TArray<AActor*> Doors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoor::StaticClass(), Doors);

	for (int i = 0; i < Doors.Num(); i++)
	{
		if (ADoor* Door = Cast<ADoor>(Doors[i]))
		{
			Door->OnDoorOpen.AddUniqueDynamic(this, &ANightGameMode::RemoveEnergyUsageLevel);
			Door->OnDoorClose.AddUniqueDynamic(this, &ANightGameMode::AddEnergyUsageLevel);
		}
	}

	//Set corridor light events
	TArray<AActor*> Lights;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACorridorLight::StaticClass(), Lights);

	for (int i = 0; i < Lights.Num(); i++)
	{
		if (ACorridorLight* Light = Cast<ACorridorLight>(Lights[i]))
		{
			Light->OnLightON.AddUniqueDynamic(this, &ANightGameMode::AddEnergyUsageLevel);
			Light->OnLightOFF.AddUniqueDynamic(this, &ANightGameMode::RemoveEnergyUsageLevel);
		}
	}

	//Timer setup
	GetWorldTimerManager().SetTimer(NightTimer, this, &ANightGameMode::AdvanceHour,PassHourTime, true);
	GetWorldTimerManager().SetTimer(PowerTimer, this, &ANightGameMode::PowerConsume, GetEnergyConsumeTime(), true);
}

void ANightGameMode::AddEnergyUsageLevel()
{
	EnergyUsageLevel = FMath::Clamp(++EnergyUsageLevel, MinEnergyUsageLevel, MaxEnergyUsageLevel);
}

void ANightGameMode::RemoveEnergyUsageLevel()
{
	EnergyUsageLevel = FMath::Clamp(--EnergyUsageLevel, MinEnergyUsageLevel, MaxEnergyUsageLevel);
}

float ANightGameMode::GetEnergyPercentage()const
{
	return (Energy/MaxEnergy) * 100;
}

float ANightGameMode::GetEnergyConsumeTime() const
{
	return FMath::Clamp(EnergyConsumeTime / EnergyUsageLevel, 0.1, 1000);
}

void ANightGameMode::OnNightEndFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Night ended"));
	GetWorldTimerManager().ClearTimer(NightTimer);
}

void ANightGameMode::OnPowerOutFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Power out"));
	GetWorldTimerManager().ClearTimer(PowerTimer);
}