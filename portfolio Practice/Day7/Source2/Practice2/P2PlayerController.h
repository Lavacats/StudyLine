// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "P2PlayerCameraManager.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "P2PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API AP2PlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	APlayerCharacter* p2PlayerCharacter;
	AP2PlayerCameraManager* p2PlayerCameraManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AP2PlayerController();
	virtual void SetupInputComponent() override;
	virtual void PostInitializeComponents() override;
	virtual void Possess(APawn* aPawn) override;

	void ForwardBack(float NewAxisValue);
	void LeftRight(float NewAxisValue);

	void LookUpDown(float NewAxisValue);
	void Turn(float NewAxisValue);
};
