// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

class AClikableBase;

UCLASS(Abstract)
class FNAF_LIKE_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Actor that will trigger the light
	UPROPERTY(EditInstanceOnly, Category = "Clikable Settings")
	TObjectPtr<AClikableBase> ClikableInteractor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Base virtual function for interaction logic
	virtual void Interact();
};
