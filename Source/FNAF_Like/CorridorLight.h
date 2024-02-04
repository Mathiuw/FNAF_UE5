// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "CorridorLight.generated.h"

class UPointLightComponent;

/**
 * 
 */
UCLASS()
class FNAF_LIKE_API ACorridorLight : public AInteractable
{
	GENERATED_BODY()

public:

	ACorridorLight();

	virtual void Interact() override;

	UFUNCTION(BlueprintCallable)
	void SetLightState(bool state);

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* PointLightComponent;

};
