// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NightGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FNAF_LIKE_API ANightGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintCallable)
	void PowerConsume();

	UFUNCTION(BlueprintCallable)
	void AdvanceHour();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	void AddEnergyUsageLevel();

	UFUNCTION(BlueprintCallable)
	void RemoveEnergyUsageLevel();

	//GETTERS
	UFUNCTION(BlueprintPure)
	int32 GetHour()const;

	UFUNCTION(BlueprintPure)
	int32 GetNight()const;

	UFUNCTION(BlueprintPure)
	int32 GetEnergyUsageLevel()const;

	UFUNCTION(BlueprintPure)
	float GetMaxEnergy()const;

	UFUNCTION(BlueprintPure)
	float GetEnergyPercentage()const;

	UFUNCTION(BlueprintPure)
	float GetEnergyConsumeTime() const;

	UFUNCTION(BlueprintPure)
	float GetPassHourTime()const;

	//SETTERS
	UFUNCTION(BlueprintCallable)
	void SetEnergy(float Amount);

protected:

	//Current night hour
	UPROPERTY(EditDefaultsOnly, category = "Night Settings")
	int32 Hour = 12;

	//Night number
	UPROPERTY(EditDefaultsOnly, category = "Night Settings")
	int32 Night = 0;

	//Level of energy usage
	UPROPERTY(EditDefaultsOnly, category = "Night Settings")
	int32 EnergyUsageLevel = 0;

	//Amount of energy available
	UPROPERTY(EditDefaultsOnly, category = "Night Settings")
	float Energy;

	//Amount of energy available
	UPROPERTY(EditDefaultsOnly, category = "Night Settings")
	float MaxEnergy = 100;

	//Amount of time to pass the hour
	UPROPERTY(EditDefaultsOnly, category = "Night Settings")
	float PassHourTime = 30;

	//Amount of time to consume power
	UPROPERTY(EditDefaultsOnly, category = "Night Settings")
	float EnergyConsumeTime = 15;

	//MIN and MAX for energy levels
	int32 MinEnergyUsageLevel = 1;
	int32 MaxEnergyUsageLevel = 50;
};
