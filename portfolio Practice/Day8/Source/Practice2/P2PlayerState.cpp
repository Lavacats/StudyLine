// Fill out your copyright notice in the Description page of Project Settings.

#include "P2PlayerState.h"

AP2PlayerState::AP2PlayerState()
{
	EPlayerState = E_PlayerState::Player_IDLE;
	preEPlayerState = E_PlayerState::Player_IDLE;
}

E_PlayerState AP2PlayerState::getCurPlayerState()
{
	return EPlayerState;
}

void AP2PlayerState::setPlayerState(E_PlayerState setValue)
{
	preEPlayerState = EPlayerState;
	EPlayerState = setValue;
}

void AP2PlayerState::checkState_And_setState(E_PlayerState isCheckValue, E_PlayerState setValue)
{
	if (EPlayerState == isCheckValue) {
		setPlayerState(setValue);
	}
}
