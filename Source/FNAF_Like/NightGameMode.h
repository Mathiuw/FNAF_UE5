// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NightGameMode.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNightEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPowerOut);

UCLASS()
class FNAF_LIKE_API ANightGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintCallable)
	void PowerConsume();

	UFUNCTION(BlueprintCallable)
	void AddEnergyUsageLevel();

	UFUNCTION(BlueprintCallable)
	void RemoveEnergyUsageLevel();

	UFUNCTION(BlueprintCallable)
	void AdvanceHour();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnNightEnd OnNightEnd;
	UPROPERTY(BlueprintAssignable)
	FOnPowerOut OnPowerOut;

	//GETTERS
	UFUNCTION(BlueprintPure)
	float GetEnergyPercentage()const;

	UFUNCTION(BlueprintPure)
	float GetEnergyConsumeTime() const;

protected:

	UFUNCTION()
	void OnNightEndFunc();
	UFUNCTION()
	void OnPowerOutFunc();

	//Current night hour
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Night Settings")
	int32 Hour = 12;

	//Night number
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Night Settings")
	int32 Night = 0;

	//Level of energy usage
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Night Settings")
	int32 EnergyUsageLevel = 0;

	//Amount of energy available
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Night Settings")
	float Energy;

	//Amount of energy available
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Night Settings")
	float MaxEnergy = 100;

	//Amount of time to pass the hour
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Night Settings")
	float PassHourTime = 30;

	//Amount of time to consume power
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Night Settings")
	float EnergyConsumeTime = 15;

	//MIN and MAX for energy levels
	int32 MinEnergyUsageLevel = 1;
	int32 MaxEnergyUsageLevel = 50;

	//Timers
	FTimerHandle NightTimer;
	FTimerHandle PowerTimer;
};
