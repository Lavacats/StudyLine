// Fill out your copyright notice in the Description page of Project Settings.

#include "P2PlayerState.h"

AP2PlayerState::AP2PlayerState()
{
	EPlayerState = E_PlayerState::Player_IDLE;
	preEPlayerState = E_PlayerState::Player_CROUCH;
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
