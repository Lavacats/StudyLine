// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerState.h"
#include "ABGameInstance.h"

AABPlayerState::AABPlayerState()
{
	CharacterLevel = 1;
	// 현재 캐릭터의 레벨1
	GameScore = 0;
	// 게임 스코어 0
	Exp = 0;
	// 시작 경험치 0
}

int32 AABPlayerState::GetGameScore() const
{
	return GameScore;
	// 게임 스코어의 값을 반환합니다
}

int32 AABPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
	// 캐릭터 레벨의 값을 반환합니다
}

float AABPlayerState::GetExpRatio() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
		return 0.0f;
	// 경험치가 0보다 작으면 0을 반환한다

	float Result = (float)Exp / (float)CurrentStatData->NextExp;
	ABLOG(Warning, TEXT("Radio : %f, Current : %d, Next: %d"), Result, Exp, CurrentStatData->NextExp);
	return Result;
	// 최대경험치/현재 경험치 퍼센트를 반환한다.
}

bool AABPlayerState::AddExp(int32 IncomeExp)
{
	if (CurrentStatData->NextExp == -1)
		return false;
	// NextExp가 -1이면 false를 반환한다.

	bool DidLevelUp = false;
	Exp = Exp + IncomeExp;
	if (Exp >= CurrentStatData->NextExp) {
		Exp -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}
	// 경험치가 NextExp보다 크가면 현재 경험치에서 NextExp를 빼고 레벨을 1올린다.

	OnPlayerStateChanged.Broadcast();
	// 플레이어의 스탯에 변화가 있을때 실행할 딜리게이트 함수를 실행합니다.
	return DidLevelUp;
}

void AABPlayerState::AddGameScore()
{
	GameScore++;
	OnPlayerStateChanged.Broadcast();
	// 게임스코어를 1점 더하고 OnPlayerStateChnage의 함수를 실행시킵니다.
}

void AABPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Destiny"));
	// 플레이어 이름(playerState원래 가지고있던 정보)를 Destiny라 세팅합니다
	SetCharacterLevel(5);
	// 캐릭터 레벨으 5로 둡니다
	GameScore = 0;
	// 게임점수를 0으로 둡니다.
	Exp = 0;
	// 시작 경험치를 0으로 둡니다
}

void AABPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	ABCHECK(nullptr != ABGameInstance);
	// 게임인스탄스를 불러옵니다.

	CurrentStatData = ABGameInstance->GetABCharacterData(NewCharacterLevel);
	ABCHECK(nullptr != CurrentStatData);
	// 캐릭터 데이터를 불러옵니다

	CharacterLevel = NewCharacterLevel;
	// 현재 캐릭터 정보를 덧씌웁니다.
}
