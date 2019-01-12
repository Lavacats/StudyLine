// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerState.h"
#include "ABGameInstance.h"
#include "ABSaveGame.h"

AABPlayerState::AABPlayerState()
{
	CharacterLevel = 1;
	// 현재 캐릭터의 레벨1
	GameScore = 0;
	// 게임 스코어 0
	Exp = 0;
	// 시작 경험치 0
	GameHighScore = 0;
	// 게임 최고 점수 0점
	SaveSlotName = TEXT("Player1");
	// 세이브 슬롯의 이름을 Palyer1이라한다
	CharacterIndex = 0;
	// 캐릭터 인덱스 초기화
}

int32 AABPlayerState::GetGameScore() const
{
	return GameScore;
	// 게임 스코어의 값을 반환합니다
}

int32 AABPlayerState::GetGameHighScore() const
{
	return GameHighScore;
}

int32 AABPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
	// 캐릭터 레벨의 값을 반환합니다
}

int32 AABPlayerState::GetChracterIndex() const
{
	return CharacterIndex;
	// 캐릭터 인덱스 값 반환
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
	SavePlayerData();
	// 플레이어 데이터를 저장합니다.
	return DidLevelUp;
}

void AABPlayerState::AddGameScore()
{
	GameScore++;
	if (GameScore >= GameHighScore) {
		GameHighScore = GameScore;
		// 현재 게임 점수가 최고 점수보다 높다면 최고 점수를 현재 점수로 바꿉니다.
	}
	OnPlayerStateChanged.Broadcast();
	// 게임스코어를 1점 더하고 OnPlayerStateChnage의 함수를 실행시킵니다.
	SavePlayerData();
	// 플레이어 데이터를 저장합니다.
}

void AABPlayerState::InitPlayerData()
{
	//SetPlayerName(TEXT("Destiny"));
	//// 플레이어 이름(playerState원래 가지고있던 정보)를 Destiny라 세팅합니다
	//SetCharacterLevel(5);
	//// 캐릭터 레벨으 5로 둡니다
	//GameScore = 0;
	//// 게임점수를 0으로 둡니다.
	//Exp = 0;
	//// 시작 경험치를 0으로 둡니다

	auto ABSaveGame = Cast<UABSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	// 플레이어 스태이트에서 세이브 데이터를 가져옵니다
	if (nullptr == ABSaveGame) {
		ABSaveGame = GetMutableDefault<UABSaveGame>();
		// 세이브 데이터를 정상적으로 불러왔다면 변수에 저장합니다.
	}

	SetPlayerName(ABSaveGame->PlayerName);
	// 세이브 데이터에서 플레이어 이름을 가져와 세팅합니다
	SetCharacterLevel(ABSaveGame->Level);
	// 세이브 데이터에서 캐릭터 레벨을 가져와 세팅합니다
	GameScore = 0;
	// 게임 점수는 0점으로 둡니다
	GameHighScore = ABSaveGame->HighScore;
	// 세이브 데이터에서 게임의 최고 점수를 가져와 세팅합니다
	Exp = ABSaveGame->Exp;
	// 세이브 데이터에서 Exp데이터를 가져와 세팅합니다.
	SavePlayerData();
	// 플레이어 데이터를 저장합니다.
	CharacterIndex = ABSaveGame->CharacterIndex;
	// 캐릭터 인덱스는 세이브데이터의 캐릭터 인덱스 입니다.
}

void AABPlayerState::SavePlayerData()
{
	UABSaveGame* NewPlayerData = NewObject <UABSaveGame>();
	// 플레이어 데이터를 세이브할 변수를 선언합니다
	NewPlayerData->PlayerName = GetPlayerName();
	// 세이브 데이터에 플레이어 이름을 입력합니다
	NewPlayerData->Level = CharacterLevel;
	// 세이브 데이터에 캐릭터 레벨을 입력합니다
	NewPlayerData->Exp = Exp;
	// 세이브 데이터에 경험치 데이터를 입력합니다
	NewPlayerData->HighScore = GameHighScore;
	// 세이브 데이터에 최대 점수 데이터를 입력합니다
	NewPlayerData->CharacterIndex = CharacterIndex;
	// 세이브 데이터에 캐릭터 인덱스에 현재 캐릭터 인덱스를 입력합니다.
	
	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0)) {
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
	// 입력한 slot에 데이터가 입력되었는지 확인합니다.
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
