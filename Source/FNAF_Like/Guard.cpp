// Fill out your copyright notice in the Description page of Project Settings.


#include "Guard.h"
#include "GuardController.h"


void AGuard::BeginPlay()
{
	Super::BeginPlay();

}


void AGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move camera
	MoveCameraByCursor(DeltaTime);
}


void AGuard::MoveCameraByCursor(float DeltaTime)
{
	if (AGuardController* GuardController = Cast<AGuardController>(GetController()))
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