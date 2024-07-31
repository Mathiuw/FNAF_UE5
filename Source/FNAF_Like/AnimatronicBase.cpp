// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimatronicBase.h"

// Sets default values
AAnimatronicBase::AAnimatronicBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimatronicBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnAnimatronicPathCompletion.AddUniqueDynamic(this, &AAnimatronicBase::OnAnimatronicPathCompletionFunc);

}

// Called every frame
void AAnimatronicBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAnimatronicBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAnimatronicBase::OnAnimatronicPathCompletionFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Animatronic broke into the office"));

}

void AAnimatronicBase::CompletePath()
{
	OnAnimatronicPathCompletion.Broadcast();
}