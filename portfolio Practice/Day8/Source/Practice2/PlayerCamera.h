// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCamera.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API UPlayerCamera : public UCameraComponent
{
	GENERATED_BODY()

public:
	UPlayerCamera();

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

public:
	void setSpringArmCameraInRoot(UCapsuleComponent* root);
};
