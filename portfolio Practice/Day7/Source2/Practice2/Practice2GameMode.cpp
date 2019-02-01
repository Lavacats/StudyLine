// Fill out your copyright notice in the Description page of Project Settings.

#include "Practice2GameMode.h"
#include "PlayerCharacter.h"
#include "P2PlayerController.h"
APractice2GameMode::APractice2GameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AP2PlayerController::StaticClass();
	//PlayerCameraManager;
}