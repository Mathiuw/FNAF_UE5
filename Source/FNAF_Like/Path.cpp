// Fill out your copyright notice in the Description page of Project Settings.


#include "Path.h"
#include "PathPoint.h"
#include "DrawDebugHelpers.h"
#include "Door.h"

// Sets default values
APath::APath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

APathPoint* APath::GetPoint(int index) const
{
	if (!Points.IsValidIndex(index))
	{
		return nullptr;
	}

	return Points[index];
}

bool APath::IsNextPointValid(int index) const
{
	if (Points.IsValidIndex(++index))
	{
		return true;
	}
	else return false;

}

// Called when the game starts or when spawned
void APath::BeginPlay()
{
	Super::BeginPlay();

	DEBUGDrawLinePoints();

}

void APath::DEBUGDrawLinePoints()
{

	for (int i = 0; i < Points.Num(); i++)
	{
		//Nothing on array
		if (Points.IsEmpty())
		{
			UE_LOG(LogTemp, Display, TEXT("Path: ARRAY IS EMPTY"));
			return;
		}

		APathPoint* NextPoint = nullptr;

		if (Points.IsValidIndex(i + 1))
		{
			//Get next point
			NextPoint = Points[i + 1];
		}

		if (!Points.IsValidIndex(i))
		{
			UE_LOG(LogTemp, Display, TEXT("Path: FAILED GET POINT"));
			return;
		}

		if (!NextPoint)
		{
			UE_LOG(LogTemp, Display, TEXT("Path: FAILED GET NEXT POINT"));
			return;
		}

		//Draw line
		DrawDebugLine(GetWorld(), Points[i]->GetActorLocation(), NextPoint->GetActorLocation(), FColor::Green, true);
	}
}

// Called every frame
void APath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

