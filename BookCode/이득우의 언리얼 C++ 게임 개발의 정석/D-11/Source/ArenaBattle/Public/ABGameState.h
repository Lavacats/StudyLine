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
	// ���� ������ ��ȯ�մϴ�.
	void AddGameScore();
	// ���������� ���մϴ� (�Ƹ� 1���� ������ ������ �ȹ޴°Ű���)

	void SetGameCleared();
	bool IsGameCleared() const;
	// ���� Ŭ���Լ�
private:
	UPROPERTY(Transient)
	int32 TotalGameScore;
	// ���� ����

	UPROPERTY(Transient)
	bool bGameCleared;
	// ���� Ŭ���� �Ұ�
};
