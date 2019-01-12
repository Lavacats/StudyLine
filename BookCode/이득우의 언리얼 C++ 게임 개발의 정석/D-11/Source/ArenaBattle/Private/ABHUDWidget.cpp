// Fill out your copyright notice in the Description page of Project Settings.

#include "ABHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "ABCharacterStatComponent.h"
#include "ABPlayerState.h"

void UABHUDWidget::BindCharacterStat(class UABCharacterStatComponent* CharacterStat)
{
	ABCHECK(nullptr != CharacterStat);
	// 캐릭터 스텟이 없다면 오류로그를 반환한다.
	CurrentCharacterStat = CharacterStat;
	// 현재 캐릭터 스텟을 덧씌우고
	CharacterStat->OnHPChanged.AddUObject(this, &UABHUDWidget::UpdateCharacterStat);
	// OnHPChaged 함수에 UpdateCharacterStat 함수를 더한다
}

void UABHUDWidget::BindPlayerState(AABPlayerState * PlayerState)
{
	ABCHECK(nullptr != PlayerState);
	// 플레이어 스텟이 없다면 오류로그를 반환한다.
	CurrentPlayerState = PlayerState;
	// 현재 플레이어 스텟을 덧씌우고
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UABHUDWidget::UpdatePlayerState);
	// OnHPChaged 함수에 UpdateCharacterStat 함수를 더한다
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

	// 캐릭터 UI들을 연결해줍니다.
}

void UABHUDWidget::UpdateCharacterStat()
{
	ABCHECK(CurrentCharacterStat.IsValid());

	HPBar->SetPercent(CurrentCharacterStat->GetHPRatio());
	// HP 퍼센트를 HPbar에 전해줍니다.
}

void UABHUDWidget::UpdatePlayerState()
{
	ABCHECK(CurrentPlayerState.IsValid());

	ExpBar->SetPercent(CurrentPlayerState->GetExpRatio());
	// 경험치 바의 퍼센트지를 갱신시켜줍니다.
	PlayerName->SetText(FText::FromString(CurrentPlayerState->GetPlayerName()));
	PlayerLevel->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCharacterLevel())));
	CurrentScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameScore())));
	// 플레이어 정보를 갱신시켜줍니다.

	HighScore->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameHighScore())));
	// 플레이어 데이터에서 최대 점수를 가져와 갱신시킵니다.
}
