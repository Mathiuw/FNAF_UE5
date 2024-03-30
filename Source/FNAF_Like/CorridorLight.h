// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "CorridorLight.generated.h"

class UPointLightComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightON);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightOFF);

/**
 * 
 */
UCLASS()
class FNAF_LIKE_API ACorridorLight : public AInteractable
{
	GENERATED_BODY()

public:

	ACorridorLight();

	//Sets the light state
	UFUNCTION(BlueprintCallable)
	void SetLightState(bool state);

	//Light ON delegate event
	UPROPERTY(BlueprintAssignable)
	FOnLightON OnLightON;

	//Light OFF delegate event
	UPROPERTY(BlueprintAssignable)
	FOnLightOFF OnLightOFF;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Light component
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* PointLightComponent;

};
