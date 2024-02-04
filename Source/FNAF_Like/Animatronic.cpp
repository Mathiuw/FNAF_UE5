// Fill out your copyright notice in the Description page of Project Settings.


#include "Animatronic.h"

// Sets default values
AAnimatronic::AAnimatronic()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

APath* AAnimatronic::GetPath() const
{

	return Path;
}

// Called when the game starts or when spawned
void AAnimatronic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnimatronic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAnimatronic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

