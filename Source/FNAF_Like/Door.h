// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Door.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorClose);

/**
 * 
 */
UCLASS()
class FNAF_LIKE_API ADoor : public AInteractable
{
	GENERATED_BODY()
	
public:

	ADoor();

	virtual void Interact() override;

	//Open/Close the door
	UFUNCTION(BlueprintCallable)
	void SetDoorState(bool state);

	//GETTERS
	UFUNCTION(BlueprintCallable)
	bool GetIsClosed() const;

	FOnDoorOpen OnDoorOpen;
	FOnDoorClose OnDoorClose;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPowerOutFunc();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings")
	bool IsClosed;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorFrameMesh;

};