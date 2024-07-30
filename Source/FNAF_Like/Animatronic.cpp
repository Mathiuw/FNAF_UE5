// Fill out your copyright notice in the Description page of Project Settings.


#include "Animatronic.h"

// Sets default values
AAnimatronic::AAnimatronic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimatronic::BeginPlay()
{
	Super::BeginPlay();
	
	OnAnimatronicPathCompletion.AddUniqueDynamic(this, &AAnimatronic::OnAnimatronicPathCompletionFunc);

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

void AAnimatronic::OnAnimatronicPathCompletionFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Animatronic broke into the office"));

}

void AAnimatronic::CompletePath()
{
	OnAnimatronicPathCompletion.Broadcast();
}