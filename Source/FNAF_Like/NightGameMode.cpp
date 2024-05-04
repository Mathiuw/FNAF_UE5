// Fill out your copyright notice in the Description page of Project Settings.


#include "NightGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Door.h"
#include "CorridorLight.h"

void ANightGameMode::PowerConsume()
{
	if (Energy > 0)
	{
		Energy--;
	}
	else
	{
		OnPowerOut.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Red, TEXT("Power out"));
		GetWorldTimerManager().ClearTimer(PowerTimer);
	}
}

void ANightGameMode::AdvanceHour()
{ 
	if (Hour == 12)
	{
		Hour = 1;
		return;
	}
	else if (Hour == 6)
	{
		OnNightEnd.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 2.5f, FColor::Green, TEXT("Night ended"));
		GetWorldTimerManager().ClearTimer(NightTimer);
	}

	Hour = FMath::Clamp(++Hour, 1, 6);
}

void ANightGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Set energy to max
	Energy = MaxEnergy;

	TArray<AActor*, FDefaultAllocator> Doors;
	TArray<AActor*> Lights;

	//Set door events
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

void ANightGameMode::OnNightEndFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Night ended"));
}

void ANightGameMode::OnPowerOutFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Power out"));
}