// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "Camera/PlayerCameraManager.h"
#include "P2PlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API AP2PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	AP2PlayerCameraManager();

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	
public:
	void SetRootComponentSpringArm(USkeletalMeshComponent* Root);
	
};
