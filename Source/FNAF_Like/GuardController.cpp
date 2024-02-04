// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardController.h"
#include "Guard.h"
#include "SecurityCamera.h"

void AGuardController::SwitchCameraGuard()
{
	//Check with pawn is possesed and pick up the inverse
	if (Cast<AGuard>(GetPawn()))
	{
		if (SecurityCameras.Num() == 0)
		{
			//Dont have cameras
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("CANT FIND CAMERA"));
			}

			return;
		}

		//Posses camera
		Possess(GetSecurityCamera(GetCurrentSecurityCamera()));
	}
	else if (Cast<ASecurityCamera>(GetPawn()))
	{
		//Posses guard
		Possess(Guard);
	}

}

void AGuardController::SwitchCamera(int32 CameraIndex)
{
	if (Cast<AGuard>(GetPawn())) 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("IN GUARD, CANT CHANGE CAM"));
		}

		return;
	} 

	//Subtract camera index by 1
	int32 ArrayIndex = --CameraIndex;

	if (CurrentSecurityCameraIndex != ArrayIndex && ArrayIndex < SecurityCameras.Max())
	{
		Possess(GetSecurityCamera(ArrayIndex));
		CurrentSecurityCameraIndex = ArrayIndex;

		UE_LOG(LogTemp, Display, TEXT("CAMERA CHANGED, Array index: %d"), ArrayIndex);
	}
}

ASecurityCamera* AGuardController::GetSecurityCamera(int32 index) const
{
	return SecurityCameras[index];
}

void AGuardController::AddSecurityCamera(ASecurityCamera* SecurityCamera)
{
	SecurityCameras.Add(SecurityCamera);
}

int AGuardController::GetCurrentSecurityCamera() const
{
	return CurrentSecurityCameraIndex;
}

void AGuardController::BeginPlay()
{
	Super::BeginPlay();

	if (AGuard* GuardPawn = Cast<AGuard>(GetPawn() ) )
	{
		//Set Guard
		Guard = GuardPawn;
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("FAILED TO SET GUARD") );
		}
	}

}
