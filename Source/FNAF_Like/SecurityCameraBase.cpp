// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityCameraBase.h"
#include "Components/PointLightComponent.h"

ASecurityCameraBase::ASecurityCameraBase()
{
	CameraLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Camera Light"));
	
	CameraLight->SetupAttachment(RootComponent);
}

void ASecurityCameraBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!Disabled)
	{
		CameraLight->SetVisibility(true);
	}
}

void ASecurityCameraBase::UnPossessed()
{
	Super::UnPossessed();

	CameraLight->SetVisibility(false);
}

void ASecurityCameraBase::BeginPlay()
{
	Super::BeginPlay();

	CameraLight->SetVisibility(false);
}
