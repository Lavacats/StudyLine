// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "GameFramework/PlayerState.h"
#include "P2PlayerState.generated.h"

UENUM()
enum class E_PlayerState : uint8 {
	Player_IDLE		UMETA(DisplayName = "Player_IDLE"),
	Player_WALK		UMETA(DisplayName = "Player_WALK"),
	Player_JUMP		UMETA(DisplayName = "Player_JUMP"),
	Player_RUN		UMETA(DisplayName = "Player_RUN"),
	Player_COLLECT  UMETA(DisplayName = "Player_COLLECT"),
	Player_CROUCH	UMETA(DisplayName = "Player_CROUCH"),
	Player_PUSH		UMETA(DisplayName = "Player_PUSH"),
	Player_CLIMING	UMETA(DisplayName = "Player_CLIMING")
};

UCLASS()
class PRACTICE2_API AP2PlayerState : public APlayerState
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = State, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	E_PlayerState EPlayerState;
	UPROPERTY(Category = State, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	E_PlayerState preEPlayerState;

public:
	AP2PlayerState();

	E_PlayerState getCurPlayerState();
	E_PlayerState getPrePlayerState();
	void setPlayerState(E_PlayerState setValue);
	bool CheckCurState(E_PlayerState setValue);
	void CheckState_And_setState(E_PlayerState isCheckValue, E_PlayerState setValue);
};
