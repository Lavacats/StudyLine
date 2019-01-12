// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Blueprint/UserWidget.h"
#include "ABHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(class UABCharacterStatComponent* CharacterStat);
	// 캐릭터 스탯과 연결합니다
	void BindPlayerState(class AABPlayerState* PlayerState);
	// 플레이서 스탯가 연결합니다.

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	// 캐릭터 스탯을 업데이트 합니다
	void UpdatePlayerState();
	// 플레이어 스탯을 업데이트 합니다

private:
	TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;
	// 캐릭터 스탯
	TWeakObjectPtr<class AABPlayerState> CurrentPlayerState;
	// 플레이어 스탯

	UPROPERTY()
	class UProgressBar* HPBar;
	UPROPERTY()
	class UProgressBar* ExpBar;
	UPROPERTY()
	class UTextBlock* PlayerName;
	UPROPERTY()
	class UTextBlock* PlayerLevel;
	UPROPERTY()
	class UTextBlock* CurrentScore;
	UPROPERTY()
	class UTextBlock* HighScore;
	// 플레이어 스탯 정보 UI
	
};
