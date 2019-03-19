// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerChracterMoveController.h"

APlayerChracterMoveController::APlayerChracterMoveController()
{
	IsJump = false;
	IsMove = false;
	IsPush = false;
	IsClimming = false;
	playerSpeed = 0.5f;
	playerCurSpeed = playerSpeed;
}

void APlayerChracterMoveController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerJumpCheck();
	PlayerTracePushCheck();
	PlayerTraceClimmingCheck();
	PlayerTrace->PlayerTraceCheck(p2PlayerCharacter->GetActorLocation(), p2PlayerCharacter->GetActorForwardVector(), p2PlayerCharacter);

	float curSpeed = p2PlayerCharacter->GetVelocity().Size();

	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
		p2PlayerSate->getStaminaUseSet(true);
		if (p2PlayerSate->getStaminaPercent() < 0.1f) {
			PlayerRunStop();
			p2PlayerSate->setStaminaCharge(true);
		}
	}
	else if (p2PlayerSate->CheckCurState(E_PlayerState::Player_PUSH)) {

		if (curSpeed < 0.1f) p2PlayerSate->getStaminaUseSet(false);
		else p2PlayerSate->getStaminaUseSet(true);

		if (p2PlayerSate->getStaminaPercent() < 0.1f) {
			PlayerPushEnd();
			p2PlayerSate->setStaminaCharge(true);
		}
	}
	else if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING)) {
		p2PlayerSate->getStaminaUseSet(true);
		if (curSpeed > 0.1f) p2PlayerSate->StaminaSetting(-DeltaTime/50.0f);

		if (p2PlayerSate->getStaminaPercent() < 0.1f) {
			PlayerClimmingEnd();
			p2PlayerSate->setStaminaCharge(true);
		}
	}
	else {
		p2PlayerSate->getStaminaUseSet(false);
	}

	if (p2PlayerSate->getStaminaPercent() < 1.0f) {
		p2PlayerCharacter->getPlayerUI()->ShowStamina(true);
	}
	else {
		p2PlayerCharacter->getPlayerUI()->ShowStamina(false);
	}

}

void APlayerChracterMoveController::PlayerMoveSetting(APlayerCharacter * Character, UPlayerCharacterState * Sate, UPlayerTrace * Trace)
{
	p2PlayerCharacter=Character;
	p2PlayerSate= Sate;
	PlayerTrace= Trace;
}

void APlayerChracterMoveController::KeyDownCheck()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
		if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {
			p2PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
		}
	}
	IsMove = false;
	playerCurSpeed = playerSpeed;
}

void APlayerChracterMoveController::PlayerJumpCheck()
{
	if (IsJump){
		if (p2PlayerCharacter->GetMovementComponent()->IsFalling() && !p2PlayerSate->CheckCurState(E_PlayerState::Player_JUMP)) {
			p2PlayerSate->setPlayerState(E_PlayerState::Player_JUMP);
			
		}
		else if (p2PlayerCharacter->GetMovementComponent()->IsMovingOnGround() && p2PlayerSate->CheckCurState(E_PlayerState::Player_JUMP)) {
			p2PlayerSate->setPlayerState(p2PlayerSate->getPrePlayerState());
			IsJump = false;
		}
	}
}

void APlayerChracterMoveController::PlayerJump()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE) || p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
		p2PlayerCharacter->Jump();
		p2PlayerSate->StaminaSetting(-0.1f);
		IsJump = true;
	}
}

void APlayerChracterMoveController::PlayerRunStart()
{
	if (!p2PlayerSate->getStaminaCharge() && p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK)) {
		p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_WALK, E_PlayerState::Player_RUN);
		playerCurSpeed = playerSpeed * 1.5f;
		//p2PlayerSate->getStaminaUseSet(true);
	}
}

void APlayerChracterMoveController::PlayerRunStop()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN))
	{
		p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_RUN, E_PlayerState::Player_WALK);
		playerCurSpeed = playerSpeed;
		//p2PlayerSate->getStaminaUseSet(false);
	}
}

void APlayerChracterMoveController::PlayerCrouch()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE) ||
		p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) ||
		p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN))
	{
		p2PlayerSate->setPlayerState(E_PlayerState::Player_CROUCH);
		p2PlayerCharacter->Crouch();
	}
}

void APlayerChracterMoveController::PlayerUnCrouch()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CROUCH)) {
		p2PlayerCharacter->UnCrouch();
		p2PlayerSate->setPlayerState(p2PlayerSate->getPrePlayerState());
	}
}

void APlayerChracterMoveController::PlayerTracePushCheck()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_PUSH) || p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
		if (!p2PlayerSate->getStaminaCharge() && PlayerTrace->getTracePush() && PlayerTrace->getTraceClose() && PlayerTrace->getTraceForward() && !IsPush) {
			PlayerPushStart();
		}
		else if (!PlayerTrace->getTracePush() && !PlayerTrace->getTraceClose() && !PlayerTrace->getTraceForward() && IsPush) {
			PlayerPushEnd();
		}
	}
}

void APlayerChracterMoveController::PlayerPushStart()
{
	p2PlayerSate->setPlayerState(E_PlayerState::Player_PUSH);
	p2PlayerCharacter->GetMesh()->SetRelativeLocation(FVector(-15.0f, 0, -32.0f));
	IsPush = true;
	//p2PlayerSate->getStaminaUseSet(true);
}

void APlayerChracterMoveController::PlayerPushEnd()
{
	p2PlayerSate->setPlayerState(p2PlayerSate->getPrePlayerState());
	p2PlayerCharacter->GetMesh()->SetRelativeLocation(FVector(0, 0, -32.0f));
	IsPush = false;
	//p2PlayerSate->getStaminaUseSet(false);
}

void APlayerChracterMoveController::PlayerTraceClimmingCheck()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING) || p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN) || p2PlayerSate->CheckCurState(E_PlayerState::Player_JUMP)) {
		if (!p2PlayerSate->getStaminaCharge() && PlayerTrace->getTraceHeight() && PlayerTrace->getTraceClimming() && PlayerTrace->getTraceClose() && PlayerTrace->getTraceForward() && !IsClimming) {
			PlayerClimmingStart();
		}
		else if (!PlayerTrace->getTraceHeight() && PlayerTrace->getTraceClimming() && PlayerTrace->getTraceClose() && PlayerTrace->getTraceForward() && IsClimming) {
			IsClimming = false;

		}
		if (!PlayerTrace->getTraceClose() || !PlayerTrace->getTraceForward()) {
			if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING)) {
				PlayerClimmingEnd();
			}
		}
	}
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING) && !IsClimming) {
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorUpVector()*0.75f);
	}
}

void APlayerChracterMoveController::PlayerClimmingStart()
{
	p2PlayerSate->setPlayerState(E_PlayerState::Player_CLIMING);
	p2PlayerCharacter->GetCharacterMovement()->StopMovementImmediately();
	p2PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	IsClimming = true;
}

void APlayerChracterMoveController::PlayerClimmingEnd()
{
	p2PlayerSate->setPlayerState(p2PlayerSate->getPrePlayerState());
	p2PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
	IsClimming = false;
	playerCurSpeed = playerSpeed;
	p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorForwardVector()*2.0f);

}

void APlayerChracterMoveController::PlayerExtraState()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_Carry)) {
		PlayerTrace->ThrowObject();
	}
	else if (p2PlayerSate->getPlayerExtraState() != E_PlayerState::Player_NONE) {
		p2PlayerSate->setExtraState();
	}
}
