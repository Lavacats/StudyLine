// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerState.h"
#include "ABGameInstance.h"
#include "ABSaveGame.h"

AABPlayerState::AABPlayerState()
{
	CharacterLevel = 1;
	// ���� ĳ������ ����1
	GameScore = 0;
	// ���� ���ھ� 0
	Exp = 0;
	// ���� ����ġ 0
	GameHighScore = 0;
	// ���� �ְ� ���� 0��
	SaveSlotName = TEXT("Player1");
	// ���̺� ������ �̸��� Palyer1�̶��Ѵ�
	CharacterIndex = 0;
	// ĳ���� �ε��� �ʱ�ȭ
}

int32 AABPlayerState::GetGameScore() const
{
	return GameScore;
	// ���� ���ھ��� ���� ��ȯ�մϴ�
}

int32 AABPlayerState::GetGameHighScore() const
{
	return GameHighScore;
}

int32 AABPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
	// ĳ���� ������ ���� ��ȯ�մϴ�
}

int32 AABPlayerState::GetChracterIndex() const
{
	return CharacterIndex;
	// ĳ���� �ε��� �� ��ȯ
}

float AABPlayerState::GetExpRatio() const
{
	if (CurrentStatData->NextExp <= KINDA_SMALL_NUMBER)
		return 0.0f;
	// ����ġ�� 0���� ������ 0�� ��ȯ�Ѵ�

	float Result = (float)Exp / (float)CurrentStatData->NextExp;
	ABLOG(Warning, TEXT("Radio : %f, Current : %d, Next: %d"), Result, Exp, CurrentStatData->NextExp);
	return Result;
	// �ִ����ġ/���� ����ġ �ۼ�Ʈ�� ��ȯ�Ѵ�.
}

bool AABPlayerState::AddExp(int32 IncomeExp)
{
	if (CurrentStatData->NextExp == -1)
		return false;
	// NextExp�� -1�̸� false�� ��ȯ�Ѵ�.

	bool DidLevelUp = false;
	Exp = Exp + IncomeExp;
	if (Exp >= CurrentStatData->NextExp) {
		Exp -= CurrentStatData->NextExp;
		SetCharacterLevel(CharacterLevel + 1);
		DidLevelUp = true;
	}
	// ����ġ�� NextExp���� ũ���� ���� ����ġ���� NextExp�� ���� ������ 1�ø���.

	OnPlayerStateChanged.Broadcast();
	// �÷��̾��� ���ȿ� ��ȭ�� ������ ������ ��������Ʈ �Լ��� �����մϴ�.
	SavePlayerData();
	// �÷��̾� �����͸� �����մϴ�.
	return DidLevelUp;
}

void AABPlayerState::AddGameScore()
{
	GameScore++;
	if (GameScore >= GameHighScore) {
		GameHighScore = GameScore;
		// ���� ���� ������ �ְ� �������� ���ٸ� �ְ� ������ ���� ������ �ٲߴϴ�.
	}
	OnPlayerStateChanged.Broadcast();
	// ���ӽ��ھ 1�� ���ϰ� OnPlayerStateChnage�� �Լ��� �����ŵ�ϴ�.
	SavePlayerData();
	// �÷��̾� �����͸� �����մϴ�.
}

void AABPlayerState::InitPlayerData()
{
	//SetPlayerName(TEXT("Destiny"));
	//// �÷��̾� �̸�(playerState���� �������ִ� ����)�� Destiny�� �����մϴ�
	//SetCharacterLevel(5);
	//// ĳ���� ������ 5�� �Ӵϴ�
	//GameScore = 0;
	//// ���������� 0���� �Ӵϴ�.
	//Exp = 0;
	//// ���� ����ġ�� 0���� �Ӵϴ�

	auto ABSaveGame = Cast<UABSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	// �÷��̾� ������Ʈ���� ���̺� �����͸� �����ɴϴ�
	if (nullptr == ABSaveGame) {
		ABSaveGame = GetMutableDefault<UABSaveGame>();
		// ���̺� �����͸� ���������� �ҷ��Դٸ� ������ �����մϴ�.
	}

	SetPlayerName(ABSaveGame->PlayerName);
	// ���̺� �����Ϳ��� �÷��̾� �̸��� ������ �����մϴ�
	SetCharacterLevel(ABSaveGame->Level);
	// ���̺� �����Ϳ��� ĳ���� ������ ������ �����մϴ�
	GameScore = 0;
	// ���� ������ 0������ �Ӵϴ�
	GameHighScore = ABSaveGame->HighScore;
	// ���̺� �����Ϳ��� ������ �ְ� ������ ������ �����մϴ�
	Exp = ABSaveGame->Exp;
	// ���̺� �����Ϳ��� Exp�����͸� ������ �����մϴ�.
	SavePlayerData();
	// �÷��̾� �����͸� �����մϴ�.
	CharacterIndex = ABSaveGame->CharacterIndex;
	// ĳ���� �ε����� ���̺굥������ ĳ���� �ε��� �Դϴ�.
}

void AABPlayerState::SavePlayerData()
{
	UABSaveGame* NewPlayerData = NewObject <UABSaveGame>();
	// �÷��̾� �����͸� ���̺��� ������ �����մϴ�
	NewPlayerData->PlayerName = GetPlayerName();
	// ���̺� �����Ϳ� �÷��̾� �̸��� �Է��մϴ�
	NewPlayerData->Level = CharacterLevel;
	// ���̺� �����Ϳ� ĳ���� ������ �Է��մϴ�
	NewPlayerData->Exp = Exp;
	// ���̺� �����Ϳ� ����ġ �����͸� �Է��մϴ�
	NewPlayerData->HighScore = GameHighScore;
	// ���̺� �����Ϳ� �ִ� ���� �����͸� �Է��մϴ�
	NewPlayerData->CharacterIndex = CharacterIndex;
	// ���̺� �����Ϳ� ĳ���� �ε����� ���� ĳ���� �ε����� �Է��մϴ�.
	
	if (!UGameplayStatics::SaveGameToSlot(NewPlayerData, SaveSlotName, 0)) {
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
	// �Է��� slot�� �����Ͱ� �ԷµǾ����� Ȯ���մϴ�.
}

void AABPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
	auto ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	ABCHECK(nullptr != ABGameInstance);
	// �����ν�ź���� �ҷ��ɴϴ�.

	CurrentStatData = ABGameInstance->GetABCharacterData(NewCharacterLevel);
	ABCHECK(nullptr != CurrentStatData);
	// ĳ���� �����͸� �ҷ��ɴϴ�

	CharacterLevel = NewCharacterLevel;
	// ���� ĳ���� ������ ������ϴ�.
}
