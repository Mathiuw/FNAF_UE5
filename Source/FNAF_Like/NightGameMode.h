// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NightGameMode.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNightEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPowerOut);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimatronicUpdate);

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

	UFUNCTION(BlueprintCallable)
	void UpdateAnimatronic();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintAssignable)
	FOnNightEnd OnNightEnd;

	UPROPERTY(BlueprintAssignable)
	FOnPowerOut OnPowerOut;

	UPROPERTY(BlueprintAssignable)
	FOnGameOver OnGameOver;

	UPROPERTY(BlueprintAssignable)
	FOnAnimatronicUpdate OnAnimatronicUpdate;

	//Broadcast OnGameOver event
	UFUNCTION(BlueprintCallable)
	void EndGame();

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

	UFUNCTION()
	void OnGameOverFunc();

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

	//Amount of time to update animatronic state
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Night Settings")
	float AnimatronicUpdateTime = 10;

	//MIN and MAX for energy levels
	int32 MinEnergyUsageLevel = 1;
	int32 MaxEnergyUsageLevel = 50;

	//Timers
	FTimerHandle NightTimer;
	FTimerHandle PowerTimer;
	FTimerHandle AnimatronicTimer;
};
