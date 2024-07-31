// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardBase.h"
#include "GuardControllerBase.h"


void AGuardBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move camera
	MoveCameraByCursor(DeltaTime);
}

void AGuardBase::BeginPlay()
{
	Super::BeginPlay();

}

void AGuardBase::MoveCameraByCursor(float DeltaTime)
{
	if (AGuardControllerBase* GuardController = Cast<AGuardControllerBase>(GetController()))
	{
		//Mouse coordinates
		FVector2D MousePosition;

		//Current window resolution
		int32 ViewportX;
		int32 ViewportY;

		GuardController->GetViewportSize(ViewportX, ViewportY);

		//Check if can get the mouse position
		if (GuardController->GetMousePosition(MousePosition.X, MousePosition.Y))
		{
			float MoveSpeedDeltaTime = MoveSpeed * DeltaTime;

			if (((MousePosition.X / ViewportX) * 100) > MoveViewportPercentage)
			{
				//Turn right
				AddControllerYawInput(MoveSpeedDeltaTime);
			}
			else if (((MousePosition.X / ViewportX) * 100) < (100 - MoveViewportPercentage))
			{
				//Turn left
				AddControllerYawInput(-MoveSpeedDeltaTime);
			}
		}
	}
}