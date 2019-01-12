// Fill out your copyright notice in the Description page of Project Settings.

#include "ABHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "ABCharacterStatComponent.h"
#include "ABPlayerState.h"

void UABHUDWidget::BindCharacterStat(class UABCharacterStatComponent* CharacterStat)
{
	ABCHECK(nullptr != CharacterStat);
	// ĳ���� ������ ���ٸ� �����α׸� ��ȯ�Ѵ�.
	CurrentCharacterStat = CharacterStat;
	// ���� ĳ���� ������ �������
	CharacterStat->OnHPChanged.AddUObject(this, &UABHUDWidget::UpdateCharacterStat);
	// OnHPChaged �Լ��� UpdateCharacterStat �Լ��� ���Ѵ�
}

void UABHUDWidget::BindPlayerState(AABPlayerState * PlayerState)
{
	ABCHECK(nullptr != PlayerState);
	// �÷��̾� ������ ���ٸ� �����α׸� ��ȯ�Ѵ�.
	CurrentPlayerState = PlayerState;
	// ���� �÷��̾� ������ �������
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UABHUDWidget::UpdatePlayerState);
	// OnHPChaged �Լ��� UpdateCharacterStat �Լ��� ���Ѵ�
}

void UABHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	ABCHECK(nullptr != HPBar);

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbExp")));
	ABCHECK(nullptr != ExpBar);

	PlayerName = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPlayerName")));
	ABCHECK(nullptr != PlayerName);

	PlayerLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	ABCHECK(nullptr != PlayerLevel);

	CurrentScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurrentScore")));
	ABCHECK(nullptr != CurrentScore);

	HighScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtHighScore")));
	ABCHECK(nullptr != HighScore);

	// ĳ���� UI���� �������ݴϴ�.
}

void UABHUDWidget::UpdateCharacterStat()
{
	ABCHECK(CurrentCharacterStat.IsValid());

	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
	// HP �ۼ�Ʈ�� HPbar�� �����ݴϴ�.
}

void UABHUDWidget::UpdatePlayerState()
{
	ABCHECK(CurrentPlayerState.IsValid());

	ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());
	// ����ġ ���� �ۼ�Ʈ���� ���Ž����ݴϴ�.
	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
	CurrentScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameScore())));
	// �÷��̾� ������ ���Ž����ݴϴ�.

	HighScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameHighScore())));
	// �÷��̾� �����Ϳ��� �ִ� ������ ������ ���Ž�ŵ�ϴ�.
}
