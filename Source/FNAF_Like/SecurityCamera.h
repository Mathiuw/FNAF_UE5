// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "SecurityCamera.generated.h"

class UPointLightComponent;

/**
 * 
 */
UCLASS()
class FNAF_LIKE_API ASecurityCamera : public APawnBase
{
	GENERATED_BODY()

public:
	ASecurityCamera();

	//Called when possessed by any controller
	virtual void PossessedBy(AController* NewController) override;

	//Called when unpossessed by any controller
	virtual void UnPossessed() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPointLightComponent* CameraLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Security Camera Settings")
	FString CameraName = "Camera_Name";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Security Camera Settings")
	FString CameraSufix = "Camera_Sufix";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Security Camera Settings")
	bool Disabled = false;
};
