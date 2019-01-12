// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/GameStateBase.h"
#include "ABGameState.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AABGameState();

public:
	int32 GetTotalGameScore() const;
	// 게임 점수를 반환합니다.
	void AddGameScore();
	// 게임점수를 더합니다 (아마 1점씩 오르니 변수를 안받는거같음)

	void SetGameCleared();
	bool IsGameCleared() const;
	// 게임 클리함수
private:
	UPROPERTY(Transient)
	int32 TotalGameScore;
	// 게임 점수

	UPROPERTY(Transient)
	bool bGameCleared;
	// 게임 클리어 불값
};
