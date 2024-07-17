// Fill out your copyright notice in the Description page of Project Settings.


#include "SecurityCamera.h"
#include "Components/PointLightComponent.h"

ASecurityCamera::ASecurityCamera()
{
	CameraLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Camera Light"));
	
	CameraLight->SetupAttachment(RootComponent);
}

void ASecurityCamera::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!Disabled)
	{
		CameraLight->SetVisibility(true);
	}
}

void ASecurityCamera::UnPossessed()
{
	Super::UnPossessed();

	CameraLight->SetVisibility(false);
}

void ASecurityCamera::BeginPlay()
{
	Super::BeginPlay();

	CameraLight->SetVisibility(false);
}
