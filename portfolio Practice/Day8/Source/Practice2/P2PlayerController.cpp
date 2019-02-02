// Fill out your copyright notice in the Description page of Project Settings.

#include "P2PlayerController.h"

AP2PlayerController::AP2PlayerController()
{
	//p2PlayerSate = CreateDefaultSubobject<AP2PlayerState>(TEXT("p2PlayerSate"));

}

void AP2PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	KeyDownCheck();
}

void AP2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("MoveForwardBack"), this, &AP2PlayerController::ForwardBack);
	InputComponent->BindAxis(TEXT("MoveLeftRight"), this, &AP2PlayerController::LeftRight);
	InputComponent->BindAxis(TEXT("Turn"), this, &AP2PlayerController::Turn);
	InputComponent->BindAxis(TEXT("LookUpDown"), this, &AP2PlayerController::LookUpDown);
	
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AP2PlayerController::PlayerJump);
}

void AP2PlayerController::Possess(APawn * aPawn)
{
	Super::Possess(aPawn);
	if (aPawn) {
		p2PlayerCharacter = Cast< APlayerCharacter>(aPawn);
		p2PlayerSate = Cast< AP2PlayerState>(PlayerState);
	}
}

void AP2PlayerController::KeyDownCheck()
{
	if (!IsInputKeyDown(EKeys::W) && !IsInputKeyDown(EKeys::S) && !IsInputKeyDown(EKeys::A) && !IsInputKeyDown(EKeys::D)) {
		p2PlayerSate->checkState_And_setState(E_PlayerState::Player_WALK, E_PlayerState::Player_IDLE);

	}

}

void AP2PlayerController::ForwardBack(float NewAxisValue)
{
	p2PlayerSate->checkState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
	p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AP2PlayerController::LeftRight(float NewAxisValue)
{
	p2PlayerSate->checkState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
	p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void AP2PlayerController::LookUpDown(float NewAxisValue)
{
	p2PlayerCharacter->AddControllerPitchInput(NewAxisValue);
}

void AP2PlayerController::Turn(float NewAxisValue)
{
	p2PlayerCharacter->AddControllerYawInput(NewAxisValue);
}

void AP2PlayerController::PlayerJump()
{
	p2PlayerSate->setPlayerState(E_PlayerState::Player_JUMP);
	p2PlayerCharacter->Jump();
}
