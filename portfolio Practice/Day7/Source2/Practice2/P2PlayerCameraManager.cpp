// Fill out your copyright notice in the Description page of Project Settings.

#include "P2PlayerCameraManager.h"

AP2PlayerCameraManager::AP2PlayerCameraManager()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 150.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = false;
}

void AP2PlayerCameraManager::SetRootComponentSpringArm(USkeletalMeshComponent* Root)
{
	SpringArm->SetupAttachment(Root);
}
