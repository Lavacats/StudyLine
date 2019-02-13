// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCamera.generated.h"


UENUM()
enum class PlayerViewState : uint8 {
	View_IDLE		UMETA(DisplayName = "View_IDLE"),
	View_SHOT		UMETA(DisplayName = "View_SHOT")
};

/**
 * 
 */
UCLASS()
class PRACTICE2_API UPlayerCamera : public UCameraComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

private:
	float ArmLengthTo = 0.0f;
	float ArmRotationSpeed = 0.0f;
	PlayerViewState ViewState;

public:
	UPlayerCamera();

	void setSpringArmCameraInRoot(UCapsuleComponent* root);
	void ChangeView(PlayerViewState view);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CameraVector();
};
