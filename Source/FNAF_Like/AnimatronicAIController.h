// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AnimatronicAIController.generated.h"

class APath;

/**
 * 
 */
UCLASS()
class FNAF_LIKE_API AAnimatronicAIController : public AAIController
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "AI Settings")
	UBehaviorTree* BehaviorTree;

};
