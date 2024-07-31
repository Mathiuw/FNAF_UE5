// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardControllerBase.h"
#include "GuardBase.h"
#include "SecurityCameraBase.h"

void AGuardControllerBase::SwitchCameraGuard()
{
	//Check with pawn is possesed and pick up the inverse
	if (Cast<AGuardBase>(GetPawn()))
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
	else if (Cast<ASecurityCameraBase>(GetPawn()))
	{
		//Posses guard
		Possess(Guard);
	}

}

void AGuardControllerBase::SwitchCamera(int32 CameraIndex)
{
	if (Cast<AGuardBase>(GetPawn())) 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("IN GUARD, CANT CHANGE CAM"));
		}

		return;
	} 

	if (SecurityCameras.IsValidIndex(CameraIndex))
	{
		//Change Pawn
		Possess(SecurityCameras[CameraIndex]);
		//Update current index
		CurrentSecurityCameraIndex = CameraIndex;

		UE_LOG(LogTemp, Display, TEXT("CAMERA CHANGED, Array index: %d"), CameraIndex);
		GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, TEXT("Switched camera"));

		//Broadcast FOnSwitchCamera eventw
		OnSwitchCamera.Broadcast();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Invalid camera index"));
	}
}

void AGuardControllerBase::AddSecurityCamera(ASecurityCameraBase* SecurityCamera)
{
	SecurityCameras.Add(SecurityCamera);
}

void AGuardControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (AGuardBase* GuardPawn = Cast<AGuardBase>(GetPawn() ) )
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
