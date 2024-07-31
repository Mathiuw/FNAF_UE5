// Fill out your copyright notice in the Description page of Project Settings.


#include "NightGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "DoorBase.h"
#include "CorridorLightBase.h"
#include "SecurityCameraBase.h"
#include "GuardControllerBase.h"

void ANightGameModeBase::EndGame()
{
	OnGameOver.Broadcast();
}

float ANightGameModeBase::GetEnergyPercentage() const
{
	return (Energy / MaxEnergy) * 100;
}

float ANightGameModeBase::GetEnergyConsumeTime() const
{
	return FMath::Clamp(EnergyConsumeTime / EnergyUsageLevel, 0.1, 1000);
}

void ANightGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Set energy to max
	Energy = MaxEnergy;

	//Night end func event setup
	OnNightEnd.AddUniqueDynamic(this, &ANightGameModeBase::OnNightEndFunc);
	//Power out func event setup
	OnPowerOut.AddUniqueDynamic(this, &ANightGameModeBase::OnPowerOutFunc);
	//Game over func event setup
	OnGameOver.AddUniqueDynamic(this, &ANightGameModeBase::OnGameOverFunc);
	
	//Get all cameras and send to the AGuardController
	if (AGuardControllerBase* GuardController = Cast<AGuardControllerBase>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		TArray<AActor*> Cameras;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASecurityCameraBase::StaticClass(), Cameras);

		for (int i = 0; i < Cameras.Num(); i++)
		{
			//Camera cast
			ASecurityCameraBase* Camera = Cast<ASecurityCameraBase>(Cameras[i]);

			if (Camera)
			{
				GuardController->AddSecurityCamera(Camera);
			}
			else
			{
				//Add failed
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Failed to add camera");
			}
		}
	}

	//Set door events
	TArray<AActor*> Doors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorBase::StaticClass(), Doors);

	for (int i = 0; i < Doors.Num(); i++)
	{
		if (ADoorBase* Door = Cast<ADoorBase>(Doors[i]))
		{
			Door->OnDoorOpen.AddUniqueDynamic(this, &ANightGameModeBase::RemoveEnergyUsageLevel);
			Door->OnDoorClose.AddUniqueDynamic(this, &ANightGameModeBase::AddEnergyUsageLevel);
		}
	}

	//Set corridor light events
	TArray<AActor*> Lights;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACorridorLightBase::StaticClass(), Lights);

	for (int i = 0; i < Lights.Num(); i++)
	{
		if (ACorridorLightBase* Light = Cast<ACorridorLightBase>(Lights[i]))
		{
			Light->OnLightON.AddUniqueDynamic(this, &ANightGameModeBase::AddEnergyUsageLevel);
			Light->OnLightOFF.AddUniqueDynamic(this, &ANightGameModeBase::RemoveEnergyUsageLevel);
		}
	}

	//Timers setup
	GetWorldTimerManager().SetTimer(NightTimer, this, &ANightGameModeBase::AdvanceHour, PassHourTime, true);
	GetWorldTimerManager().SetTimer(PowerTimer, this, &ANightGameModeBase::PowerConsume, GetEnergyConsumeTime(), true);
	GetWorldTimerManager().SetTimer(AnimatronicTimer, this, &ANightGameModeBase::UpdateAnimatronic, AnimatronicUpdateTime, true);
}

void ANightGameModeBase::PowerConsume()
{
	Energy--;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "Power depleted");

	if (Energy <= 0)
	{
		//Send to all listners that power is out
		OnPowerOut.Broadcast();
	}

	//TODO: finish timer implementation
}

void ANightGameModeBase::AddEnergyUsageLevel()
{
	EnergyUsageLevel = FMath::Clamp(++EnergyUsageLevel, MinEnergyUsageLevel, MaxEnergyUsageLevel);
}

void ANightGameModeBase::RemoveEnergyUsageLevel()
{
	EnergyUsageLevel = FMath::Clamp(--EnergyUsageLevel, MinEnergyUsageLevel, MaxEnergyUsageLevel);
}

void ANightGameModeBase::AdvanceHour()
{ 
	if (Hour == 12)
	{
		Hour = 1;
		return;
	}

	Hour++;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "Advanced hour");

	if (Hour == 6)
	{
		//Send to all listners that night ended
		OnNightEnd.Broadcast();	
	}
}

void ANightGameModeBase::UpdateAnimatronic()
{
	OnAnimatronicUpdate.Broadcast();

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "Animatronics updated");
}

void ANightGameModeBase::OnNightEndFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Night ended");
	GetWorldTimerManager().ClearTimer(NightTimer);
	GetWorldTimerManager().ClearTimer(PowerTimer);
	GetWorldTimerManager().ClearTimer(AnimatronicTimer);
}

void ANightGameModeBase::OnPowerOutFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Power out");
	GetWorldTimerManager().ClearTimer(PowerTimer);
}

void ANightGameModeBase::OnGameOverFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Game Over");

}
