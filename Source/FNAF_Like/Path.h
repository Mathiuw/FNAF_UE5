// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Path.generated.h"

class APathPoint;

UCLASS()
class FNAF_LIKE_API APath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APath();

	//GETTERS
	UFUNCTION(BlueprintPure)
	APathPoint* GetPoint(int index) const;

	//BOOLEANS
	UFUNCTION(BlueprintPure)
	bool IsNextPointValid(int index) const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//DEBUG draw line between points
	void DEBUGDrawLinePoints();

	UPROPERTY(EditAnywhere, Category = "Path Settings")
	TArray<APathPoint*> Points;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
