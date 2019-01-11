// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerState.h"
#include "ABGameInstance.h"

AABPlayerState::AABPlayerState()
{
	CharacterLevel = 1;
	// ���� ĳ������ ����1
	GameScore = 0;
	// ���� ���ھ� 0
	Exp = 0;
	// ���� ����ġ 0
}

int32 AABPlayerState::GetGameScore() const
{
	return GameScore;
	// ���� ���ھ��� ���� ��ȯ�մϴ�
}

int32 AABPlayerState::GetCharacterLevel() const
{
	return CharacterLevel;
	// ĳ���� ������ ���� ��ȯ�մϴ�
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
	return DidLevelUp;
}

void AABPlayerState::AddGameScore()
{
	GameScore++;
	OnPlayerStateChanged.Broadcast();
	// ���ӽ��ھ 1�� ���ϰ� OnPlayerStateChnage�� �Լ��� �����ŵ�ϴ�.
}

void AABPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Destiny"));
	// �÷��̾� �̸�(playerState���� �������ִ� ����)�� Destiny�� �����մϴ�
	SetCharacterLevel(5);
	// ĳ���� ������ 5�� �Ӵϴ�
	GameScore = 0;
	// ���������� 0���� �Ӵϴ�.
	Exp = 0;
	// ���� ����ġ�� 0���� �Ӵϴ�
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
