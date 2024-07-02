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
		if (SecurityCameras.IsValidIndex(CurrentSecurityCameraIndex))
		{
			Possess(SecurityCameras[CurrentSecurityCameraIndex]);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Invalid camera index"));
		}
		
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

	if (SecurityCameras.IsValidIndex(CameraIndex))
	{
		Possess(SecurityCameras[CameraIndex]);
		CurrentSecurityCameraIndex = CameraIndex;

		UE_LOG(LogTemp, Display, TEXT("CAMERA CHANGED, Array index: %d"), CameraIndex);

		GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, TEXT("Switched camera"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Invalid camera index"));
	}
}

void AGuardController::AddSecurityCamera(ASecurityCamera* SecurityCamera)
{
	SecurityCameras.Add(SecurityCamera);
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
