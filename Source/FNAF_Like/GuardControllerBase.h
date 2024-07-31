// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GuardControllerBase.generated.h"

class ASecurityCameraBase;
class AGuardBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwitchCamera);

UCLASS(Abstract)
class FNAF_LIKE_API AGuardControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SwitchCameraGuard();

	UFUNCTION(BlueprintCallable)
	void SwitchCamera(int32 index);

	UFUNCTION(BlueprintCallable)
	void AddSecurityCamera(ASecurityCameraBase* SecurityCamera);

	UPROPERTY(BlueprintAssignable)
	FOnSwitchCamera OnSwitchCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Guard Settings")
	TArray<ASecurityCameraBase*> SecurityCameras;

	AGuardBase* Guard;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, category = "Guard Settings")
	int32 CurrentSecurityCameraIndex = 0;

};
