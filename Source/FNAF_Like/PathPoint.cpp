// Fill out your copyright notice in the Description page of Project Settings.


#include "PathPoint.h"
#include "DrawDebugHelpers.h"
#include "Door.h"

// Sets default values
APathPoint::APathPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

bool APathPoint::GetIsWalkable()
{
	return Walkable;
}

ADoor* APathPoint::GetDoor() const
{
	return PathPointDoor;
}

bool APathPoint::IsDoorClosed() const
{
	if (PathPointDoor)
	{
		return PathPointDoor->GetIsClosed();
	}
	else
	{
		return false;
	}
	
}

// Called when the game starts or when spawned
void APathPoint::BeginPlay()
{
	Super::BeginPlay();
	
	//Draw Point
	DrawDebugPoint(GetWorld(), GetActorLocation(), 10, FColor::Green, true);
}

// Called every frame
void APathPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}