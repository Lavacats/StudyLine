// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/Book/GameData/ABCharacterData.ABCharacterData");
	// �ʿ��� �����͸� �������� ��θ� �����ɴϴ�.
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_ABCHARACTER(*CharacterDataPath);
	// UDatable���� ��θ� �Է��� �����͸� �ҷ��ɴϴ�.
	ABCHECK(DT_ABCHARACTER.Succeeded());
	// ���������� �ҷ��Դ��� üũ�մϴ�.
	ABCharacterTable = DT_ABCHARACTER.Object;
	// DT_ABCHARACTER�� ������ ABCharacterTable�� �ֽ��ϴ�.
	ABCHECK(ABCharacterTable->RowMap.Num() > 0);
	// �Էµ� �������� 0���� ū�� Ȯ���մϤ�.
}

void UABGameInstance::Init()
{
	Super::Init();
	ABLOG(Warning, TEXT("DropExp of Level 20 ABCharacter : %d"), GetABCharacterData(20)->DropExp);
	// ������ 20�ϋ� ����ġ ������ Ȯ���մϴ�.
}

FABCharacterData * UABGameInstance::GetABCharacterData(int32 Level)
{
	return ABCharacterTable->FindRow<FABCharacterData>(*FString::FromInt(Level), TEXT(""));
	// �ԷµȰ��� �ִ� ������ ���� �н��ϴ�.
}

