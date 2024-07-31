// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "CorridorLightBase.generated.h"

class UPointLightComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightON);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightOFF);

UCLASS(Abstract)
class FNAF_LIKE_API ACorridorLightBase : public AInteractableBase
{
	GENERATED_BODY()

public:
	ACorridorLightBase();

	// Turn light ON
	UFUNCTION(BlueprintCallable)
	void SetLightON();

	// Turn light OFF
	UFUNCTION(BlueprintCallable)
	void SetLightOFF();

	// Light ON delegate event
	UPROPERTY(BlueprintAssignable)
	FOnLightON OnLightON;

	// Light OFF delegate event
	UPROPERTY(BlueprintAssignable)
	FOnLightOFF OnLightOFF;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPowerOutFunc();

	// Light component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPointLightComponent> PointLightComponent;
};
