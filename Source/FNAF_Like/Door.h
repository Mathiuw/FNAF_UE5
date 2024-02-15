// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Door.generated.h"

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
	bool IsDoorClosed() const;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	bool IsClosed;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

};