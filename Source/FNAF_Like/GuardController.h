// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GuardController.generated.h"

class ASecurityCamera;
class AGuard;

/**
 * 
 */
UCLASS()
class FNAF_LIKE_API AGuardController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void SwitchCameraGuard();

	UFUNCTION(BlueprintCallable)
	void SwitchCamera(int32 index);

	UFUNCTION(BlueprintCallable)
	ASecurityCamera* GetSecurityCamera(int32 CameraIndex)const;

	UFUNCTION(BlueprintCallable)
	void AddSecurityCamera(ASecurityCamera* SecurityCamera);

	//GETTERS
	int GetCurrentSecurityCamera()const;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, category = "Guard Settings")
	TArray<ASecurityCamera*> SecurityCameras;

	AGuard* Guard;

	UPROPERTY(visibleAnywhere, category = "Guard Settings")
	int32 CurrentSecurityCameraIndex = 0;

};
