// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animatronic.generated.h"

class APath;

UCLASS()
class FNAF_LIKE_API AAnimatronic : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimatronic();

	UFUNCTION(BlueprintPure)
	APath* GetPath() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AI Settings")
	APath* Path;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
