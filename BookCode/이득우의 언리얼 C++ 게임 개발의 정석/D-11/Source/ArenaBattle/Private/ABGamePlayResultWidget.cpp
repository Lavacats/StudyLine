// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGamePlayResultWidget.h"
#include "Components/TextBlock.h"
#include "ABGameState.h"

void UABGamePlayResultWidget::BindGameState(class AABGameState* GameState)
{
	ABCHECK(nullptr != GameState);
	CurrentGameState = GameState;
	// GameState를 불러 확인한 후 CurrentGameState 넣습니다
}

void UABGamePlayResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABCHECK(CurrentGameState.IsValid());
	// CurrentGameState가 정상적으로 불러왔는지 확인합니다.

	auto Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
	ABCHECK(nullptr != Result);
	// 결과 텍스트 박스를 담을 TEXT박스를 불러오고 확인해본다
	Result->SetText(FText::FromString(CurrentGameState->IsGameCleared() ? TEXT("Mission Complete") : TEXT("Mission Failed")));
	// 클리어 여부에 따라 Result에 들어갈 문자를 결정합니다.

	auto TotalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtTotalScore")));
	ABCHECK(nullptr != TotalScore);
	// 전체 점수 텍스트 박스를 담을 TEXT박스를 불러오고 확인해본다.
	TotalScore->SetText(FText::FromString(FString::FromInt(CurrentGameState->GetTotalGameScore())));
	// 전체 점수를 FSTring으로 받아 TotalScore에 저장합니다.
}



