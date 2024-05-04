// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "Guard.generated.h"


/**
 * 
 */
UCLASS()
class FNAF_LIKE_API AGuard : public APawnBase
{
	GENERATED_BODY()
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Guard Settings")
	float MoveViewportPercentage = 75;

	//Speed of the camera rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Guard Settings")
	float MoveSpeed = 0.5f;

	//Move the camera with the cursor
	void MoveCameraByCursor(float DeltaTime);
};
