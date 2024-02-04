// Fill out your copyright notice in the Description page of Project Settings.


#include "NightGameMode.h"

void ANightGameMode::AdvanceHour()
{ 
	if (Hour == 12)
	{
		Hour = 1;
		return;
	}

	Hour = FMath::Clamp(++Hour, 1, 6);
}

void ANightGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Implement timer and events
}

void ANightGameMode::AddEnergyUsageLevel()
{
	EnergyUsageLevel = FMath::Clamp(++EnergyUsageLevel, MinEnergyUsageLevel, MaxEnergyUsageLevel);
}

void ANightGameMode::RemoveEnergyUsageLevel()
{
	EnergyUsageLevel = FMath::Clamp(--EnergyUsageLevel, MinEnergyUsageLevel, MaxEnergyUsageLevel);
}

int32 ANightGameMode::GetHour()const
{
	return Hour;
}

int32 ANightGameMode::GetNight()const
{
	return Night;
}

int32 ANightGameMode::GetEnergyUsageLevel()const
{
	return EnergyUsageLevel;
}

float ANightGameMode::GetMaxEnergy()const
{
	return MaxEnergy;
}

float ANightGameMode::GetEnergyPercentage()const
{
	return (Energy/MaxEnergy) * 100;
}

float ANightGameMode::GetEnergyConsumeTime() const
{
	return FMath::Clamp(EnergyConsumeTime / EnergyUsageLevel, 0.1, 1000);
}

float ANightGameMode::GetPassHourTime() const
{
	return PassHourTime;
}

void ANightGameMode::SetEnergy(float Amount)
{
	Energy = Amount;
}

void ANightGameMode::PowerConsume()
{
	if (Energy > 0)
	{
		Energy--;
	}
}