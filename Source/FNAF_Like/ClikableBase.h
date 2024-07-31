// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClikableBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorReleased);

UCLASS(Abstract)
class FNAF_LIKE_API AClikableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClikableBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintPure)
	bool GetIsPressed() const;

	//Actor clicked delegate event
	UPROPERTY(BlueprintAssignable)
	FOnActorClicked OnActorClicked;

	//Actor released delegate event
	UPROPERTY(BlueprintAssignable)
	FOnActorReleased OnActorReleased;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Click event function
	UFUNCTION()
	void OnClickedFunc(AActor* Target, FKey ButtonPressed);

	//Release click event function
	UFUNCTION()
	void OnReleaseFunc(AActor* Target, FKey ButtonPressed);

	//Hover event function
	UFUNCTION()
	void OnHoverFunc(AActor* TouchedActor);

	//Check mouse is within bounds
	UFUNCTION()
	void MouseBoundCheck(AActor* TouchedActor);

	UPROPERTY(EditAnywhere, Category = "Clickable Settings")
	bool Hold = false;

	UPROPERTY(VisibleAnywhere, Category = "Clickable Settings")
	bool IsPressed = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> ClikableSkeletalMesh;
};
