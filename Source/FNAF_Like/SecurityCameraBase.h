// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "SecurityCameraBase.generated.h"

class UPointLightComponent;

UCLASS(Abstract)
class FNAF_LIKE_API ASecurityCameraBase : public APawnBase
{
	GENERATED_BODY()

public:
	ASecurityCameraBase();

	//Called when possessed by any controller
	virtual void PossessedBy(AController* NewController) override;

	//Called when unpossessed by any controller
	virtual void UnPossessed() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPointLightComponent> CameraLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Security Camera Settings")
	FString CameraName = "Camera_Name";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Security Camera Settings")
	FString CameraSuffix = "Camera_Suffix";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Security Camera Settings")
	bool Disabled = false;
};
