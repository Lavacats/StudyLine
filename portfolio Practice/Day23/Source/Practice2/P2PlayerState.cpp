// Fill out your copyright notice in the Description page of Project Settings.

#include "P2PlayerState.h"

AP2PlayerState::AP2PlayerState()
{
	EPlayerState = E_PlayerState::Player_IDLE;
	preEPlayerState = E_PlayerState::Player_CROUCH;
	playerCurHp = 0;
	playerMaxHp = 12;
	playerATK = 10;
	invincibleTime = 1.5f;
	invincible = false;
	playerCurHp = playerMaxHp;
}

E_PlayerState AP2PlayerState::getCurPlayerState()
{
	return EPlayerState;
}

E_PlayerState AP2PlayerState::getPrePlayerState()
{
	return preEPlayerState;
}

void AP2PlayerState::setPlayerState(E_PlayerState setValue)
{
	if (EPlayerState != setValue) {
		preEPlayerState = EPlayerState;
		EPlayerState = setValue;
	}
}

bool AP2PlayerState::CheckCurState(E_PlayerState setValue)
{
	bool answer = false;
	if (setValue == EPlayerState)answer = true;

	return answer;
}

void AP2PlayerState::CheckState_And_setState(E_PlayerState isCheckValue, E_PlayerState setValue)
{
	if (EPlayerState == isCheckValue) {
		setPlayerState(setValue);
	}
}

void AP2PlayerState::setPlayerCurHP(int32 value)
{
	if (!CheckCurState(E_PlayerState::Player_DEATH)) {
		if (!invincible) {
			playerCurHp += value;
			if (playerCurHp < 0)playerCurHp = 0;
			if (playerCurHp > playerMaxHp)playerCurHp = playerMaxHp;
		}

		if (playerCurHp <= 0) {
			setPlayerState(E_PlayerState::Player_DEATH);
		}
		else if (CheckCurState(E_PlayerState::Player_IDLE)) {
			setPlayerState(E_PlayerState::Player_HURT);
		}

		if (value < 0 && !invincible) {

			GetWorldTimerManager().ClearTimer(invincibleTimerHandle);
			GetWorldTimerManager().SetTimer(invincibleTimerHandle, this, &AP2PlayerState::CheckInvincibleTime, 0.5f, true, 0.0f);
			invincibleTime = 1.5f;
			invincible = true;
		}
	}
}

void AP2PlayerState::setMaxHP(int32 value)
{
	playerMaxHp = value;
}


void AP2PlayerState::CheckInvincibleTime()
{
	invincibleTime -= 0.5f;
	if (invincibleTime <= 0.0f) {
		GetWorldTimerManager().ClearTimer(invincibleTimerHandle);
		invincible = false;
	}
}
