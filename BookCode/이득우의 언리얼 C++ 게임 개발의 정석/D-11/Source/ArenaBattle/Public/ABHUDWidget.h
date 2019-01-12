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
	// ĳ���� ���Ȱ� �����մϴ�
	void BindPlayerState(class AABPlayerState* PlayerState);
	// �÷��̼� ���Ȱ� �����մϴ�.

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	// ĳ���� ������ ������Ʈ �մϴ�
	void UpdatePlayerState();
	// �÷��̾� ������ ������Ʈ �մϴ�

private:
	TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;
	// ĳ���� ����
	TWeakObjectPtr<class AABPlayerState> CurrentPlayerState;
	// �÷��̾� ����

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
	// �÷��̾� ���� ���� UI
	
};
