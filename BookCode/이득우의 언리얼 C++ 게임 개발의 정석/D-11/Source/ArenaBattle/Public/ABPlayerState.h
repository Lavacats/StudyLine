// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ArenaBattle.h"
#include "GameFramework/PlayerState.h"
#include "ABPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);
// FOnPlayerStateChangedDelegate 딜리게이트를 만듭니다.

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
	int32 GetGameHighScore() const;
	int32 GetCharacterLevel() const;
	int32 GetChracterIndex() const;
	float GetExpRatio() const;
	bool AddExp(int32 IncomeExp);
	// 플레이어 스텟을 반환받는다.

	FString SaveSlotName;

	void AddGameScore();
	// 게임 스코어를 더합니다.

	void InitPlayerData();
	// 플레이어 데이터 초기화
	void SavePlayerData();
	// 플레이어 데이터 세이브

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;
	// 플레이어 상태 변화에 따른 델리게이트

protected:
	UPROPERTY(Transient)
	int32 GameScore;
	// 게임의 진행상황을 기록하기위한 속성

	UPROPERTY(Transient)
	int32 GameHighScore;
	// 게임의 최대점수르 기록하는 속성

	UPROPERTY(Transient)
	int32 CharacterLevel;	
	// 플레이어의 레벨 정보를 표시하기 위한 속성

	UPROPERTY(Transient)
	int32 Exp;
	// 플레이어의 경험치를 나타내기 위한 속성

	UPROPERTY(Transient)
	int32 CharacterIndex;
	// 플레이어 캐릭터의 인덱스

private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	// 플레이어의 레벨을 결정합니다.
	struct FABCharacterData* CurrentStatData;
	// 플레이어의 스탯정보를저장하는변수
};