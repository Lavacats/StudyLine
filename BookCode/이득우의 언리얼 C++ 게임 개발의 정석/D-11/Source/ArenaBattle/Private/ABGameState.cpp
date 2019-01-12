// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameState.h"

AABGameState::AABGameState()
{
	TotalGameScore = 0;
	bGameCleared = false;
	// GameState의 초기하

}

int32 AABGameState::GetTotalGameScore() const
{
	return TotalGameScore;
}

void AABGameState::AddGameScore()
{
	TotalGameScore++;
}

void AABGameState::SetGameCleared()
{
	bGameCleared = true;
}

bool AABGameState::IsGameCleared() const
{
	return bGameCleared;
}
