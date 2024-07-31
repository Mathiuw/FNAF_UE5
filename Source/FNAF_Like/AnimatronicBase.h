// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimatronicBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimatronicPathCompletion);

UCLASS(Abstract)
class FNAF_LIKE_API AAnimatronicBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimatronicBase();

	// Delegate when animatronic enters the office, completing his path
	UPROPERTY(BlueprintAssignable)
	FOnAnimatronicPathCompletion OnAnimatronicPathCompletion;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Path complete event function
	UFUNCTION()
	void OnAnimatronicPathCompletionFunc();

	// Broadcast the FOnAnimatronicPathCompletion delegate
	UFUNCTION(BlueprintCallable)
	void CompletePath();

};