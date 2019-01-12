// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "ABGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FABCharacterData : public FTableRowBase
{
	GENERATED_BODY();
public:
	FABCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};


/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UABGameInstance();

	virtual void Init() override;
	FABCharacterData* GetABCharacterData(int32 Level);
	//데이터를 받으면 위에서 선언한 구조체로 반환한다.

	FStreamableManager StreamableManager;
	// 게임 진행 중에 비동기 방식으로 애셋을 로딩하는 클래스
	// 하나만 활성화 하는것이 좋다

private:
	UPROPERTY()
	class UDataTable* ABCharacterTable;
	// 데이터 테이블을 관리할수있는 DataTable을 선언해 엑세에서 읽은 데이터를 관리합니다.

};
