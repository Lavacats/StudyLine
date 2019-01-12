// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/Book/GameData/ABCharacterData.ABCharacterData");
	// 필요한 데이터를 레지스터 경로를 가져옵니다.
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_ABCHARACTER(*CharacterDataPath);
	// UDatable으로 경로를 입력해 데이터를 불러옵니다.
	ABCHECK(DT_ABCHARACTER.Succeeded());
	// 성공적으로 불러왔는지 체크합니다.
	ABCharacterTable = DT_ABCHARACTER.Object;
	// DT_ABCHARACTER의 정보를 ABCharacterTable에 넣습니다.
	ABCHECK(ABCharacterTable->RowMap.Num() > 0);
	// 입력된 정보수가 0보다 큰지 확인합니ㅏ.
}

void UABGameInstance::Init()
{
	Super::Init();
	ABLOG(Warning, TEXT("DropExp of Level 20 ABCharacter : %d"), GetABCharacterData(20)->DropExp);
	// 레벵리 20일떄 경험치 정보를 확인합니다.
}

FABCharacterData * UABGameInstance::GetABCharacterData(int32 Level)
{
	return ABCharacterTable->FindRow<FABCharacterData>(*FString::FromInt(Level), TEXT(""));
	// 입력된값에 있는 엑셀의 값을 읽습니다.
}

