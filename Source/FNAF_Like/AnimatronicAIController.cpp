// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimatronicAIController.h"
#include "Path.h"
#include "PathPoint.h"

void AAnimatronicAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
	
}
