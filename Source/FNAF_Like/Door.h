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
UCLASS(Abstract)
class FNAF_LIKE_API ADoor : public AInteractable
{
	GENERATED_BODY()
	
public:

	ADoor();

	virtual void Interact() override;

	// Toggle the door state
	UFUNCTION(BlueprintCallable)
	void ToggleDoorState();

	UFUNCTION(BlueprintCallable)
	bool GetIsClosed() const;

	// Delegates
	FOnDoorOpen OnDoorOpen;
	FOnDoorClose OnDoorClose;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPowerOutFunc();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Settings")
	bool IsClosed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> DoorFrameMesh;

};