// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCamera.h"

UPlayerCamera::UPlayerCamera()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	this->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength =150.0f;
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = false;

}

void UPlayerCamera::setSpringArmCameraInRoot(UCapsuleComponent * root)
{
	SpringArm->SetupAttachment(root);
}
