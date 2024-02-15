// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathPoint.generated.h"

class ADoor;

UCLASS()
class FNAF_LIKE_API APathPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathPoint();

	//GETTERS
	UFUNCTION(BlueprintPure)
	bool GetIsWalkable();

	UFUNCTION(BlueprintPure)
	ADoor* GetDoor() const;

	//BOOLEANS
	UFUNCTION(BlueprintPure)
	bool IsDoorClosed() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Path Point Settings")
	bool Walkable = false;

	UPROPERTY(EditAnywhere, Category = "Path Point Settings")
	ADoor* PathPointDoor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};