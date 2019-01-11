// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ArenaBattle.h"
#include "GameFramework/PlayerState.h"
#include "ABPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);
// FOnPlayerStateChangedDelegate ��������Ʈ�� ����ϴ�.

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AABPlayerState();

	int32 GetGameScore() const;
	int32 GetCharacterLevel() const;
	float GetExpRatio() const;
	bool AddExp(int32 IncomeExp);
	// �÷��̾� ������ ��ȯ�޴´�.

	void AddGameScore();
	// ���� ���ھ ���մϴ�.

	void InitPlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;
	// �÷��̾� ���� ��ȭ�� ���� ��������Ʈ

protected:
	UPROPERTY(Transient)
	int32 GameScore;
	// ������ �����Ȳ�� ����ϱ����� �Ӽ�

	UPROPERTY(Transient)
	int32 CharacterLevel;	
	// �÷��̾��� ���� ������ ǥ���ϱ� ���� �Ӽ�

	UPROPERTY(Transient)
	int32 Exp;
	// �÷��̾��� ����ġ�� ��Ÿ���� ���� �Ӽ�

private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	// �÷��̾��� ������ �����մϴ�.
	struct FABCharacterData* CurrentStatData;
	// �÷��̾��� ���������������ϴº���
};