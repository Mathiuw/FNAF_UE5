// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClikableBase.generated.h"

class AInteractable;

UCLASS()
class FNAF_LIKE_API AClikableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClikableBase();

	UFUNCTION(BlueprintPure)
	bool GetIsPressed() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Click event function
	UFUNCTION()
	void OnClickedFunc(AActor* Target, FKey ButtonPressed);

	//Hover event function
	UFUNCTION()
	void OnHoverFunc(AActor* TouchedActor);

	//Check mouse is within bounds
	UFUNCTION()
	void MouseBoundCheck(AActor* TouchedActor);

	void ActivateInteractableActor();

	UPROPERTY(EditAnywhere, Category = "Clickable Settings")
	AInteractable* InteractableActor;

	UPROPERTY(EditAnywhere, Category = "Clickable Settings")
	bool Hold = false;

	UPROPERTY(VisibleAnywhere, Category = "Clickable Settings")
	bool IsPressed = false;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* ClikableSkeletalMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
