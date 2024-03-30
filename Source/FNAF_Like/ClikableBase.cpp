// Fill out your copyright notice in the Description page of Project Settings.


#include "ClikableBase.h"

// Sets default values
AClikableBase::AClikableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClikableSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ClikableSkeletalMesh");
	RootComponent = ClikableSkeletalMesh;

}

bool AClikableBase::GetIsPressed() const
{
	return IsPressed;
}

// Called when the game starts or when spawned
void AClikableBase::BeginPlay()
{
	Super::BeginPlay();

	//Click Event
	OnClicked.AddUniqueDynamic(this, &AClikableBase::OnClickedFunc);

	if (Hold)
	{
		//Release Click Event
		OnReleased.AddUniqueDynamic(this, &AClikableBase::OnClickedFunc);

		//Mouse Bound Check Event
		OnEndCursorOver.AddUniqueDynamic(this, &AClikableBase::MouseBoundCheck);
	}

	//Cursor Hover Events
	OnBeginCursorOver.AddUniqueDynamic(this, &AClikableBase::OnHoverFunc);
	OnEndCursorOver.AddUniqueDynamic(this, &AClikableBase::OnHoverFunc);
}

void AClikableBase::OnClickedFunc(AActor* Target, FKey ButtonPressed)
{
	IsPressed = !IsPressed;

	OnActorClicked.Broadcast(IsPressed);
}

void AClikableBase::OnReleaseFunc(AActor* Target, FKey ButtonPressed)
{
	IsPressed = false;

	OnActorReleased.Broadcast(IsPressed);
}

void AClikableBase::OnHoverFunc(AActor* TouchedActor)
{
	ClikableSkeletalMesh->SetRenderCustomDepth(!ClikableSkeletalMesh->bRenderCustomDepth);

}

void AClikableBase::MouseBoundCheck(AActor* TouchedActor)
{
	IsPressed = false;

	OnActorReleased.Broadcast(IsPressed);
}

// Called every frame
void AClikableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}