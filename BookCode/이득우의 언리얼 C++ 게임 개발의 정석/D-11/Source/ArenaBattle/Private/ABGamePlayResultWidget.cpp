// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGamePlayResultWidget.h"
#include "Components/TextBlock.h"
#include "ABGameState.h"

void UABGamePlayResultWidget::BindGameState(class AABGameState* GameState)
{
	ABCHECK(nullptr != GameState);
	CurrentGameState = GameState;
	// GameState�� �ҷ� Ȯ���� �� CurrentGameState �ֽ��ϴ�
}

void UABGamePlayResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABCHECK(CurrentGameState.IsValid());
	// CurrentGameState�� ���������� �ҷ��Դ��� Ȯ���մϴ�.

	auto Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
	ABCHECK(nullptr != Result);
	// ��� �ؽ�Ʈ �ڽ��� ���� TEXT�ڽ��� �ҷ����� Ȯ���غ���
	Result->SetText(FText::FromString(CurrentGameState->IsGameCleared() ? TEXT("Mission Complete") : TEXT("Mission Failed")));
	// Ŭ���� ���ο� ���� Result�� �� ���ڸ� �����մϴ�.

	auto TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtTotalScore")));
	ABCHECK(nullptr != TotalScore);
	// ��ü ���� �ؽ�Ʈ �ڽ��� ���� TEXT�ڽ��� �ҷ����� Ȯ���غ���.
	TotalScore->SetText(FText::FromString(FString::FromInt(CurrentGameState->GetTotalGameScore())));
	// ��ü ������ FSTring���� �޾� TotalScore�� �����մϴ�.
}



