// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacterWidget.h"

void UABCharacterWidget::BindCharacterStat(UABCharacterStatComponent * NewCharacterStat) {

	ABCHECK(nullptr != NewCharacterStat);
	// NewChaacterStat를 정상적으로 읽었는지 확인합니다.

	CurrentCharacterStat = NewCharacterStat;
	// 현재 캐릭터 스테이트에 NewCharacterStat를 넣습니다.

	//NewCharacterStat->OnHPChanged.AddLambda([this]()->void {
	//	if (CurrentCharacterStat.IsValid()) {
	//		ABLOG(Warning, TEXT("HPRadtio : %f"), CurrentCharacterStat->GetHPRatio());
	//		// CurrentCharacterStat를 성공적으로 불러왔다면 CurrentCharacterStat의 HP비율을 로그로 출력합니다.
	//	}
	//});

	NewCharacterStat->OnHPChanged.AddUObject(this, &UABCharacterWidget::UpdateHPWidget);
	//  NewCharacterStat에 UpdateHPWidget을 OnHpChanged 이벤트에서 실행되도록 더한다.
}

void UABCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Override돼었으므로 부모도 같이 실행시켜줍니다.
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBAR")));
	// HPProgressBar를 불러옵니다.
	ABCHECK(nullptr != HPProgressBar);
	// 프로그래스바를 정상적으로 불러왔는지 체크합니다.
	UpdateHPWidget();
	// HP바를 업데이트합니다.
}

void UABCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid()) {
		// CurrentCharacterStat 이 존재하고
		if (nullptr != HPProgressBar) {
			// HPProgressBar가 있을 때
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
			// 프로그래스바의 Percetn를 CurrentCharacterStat에서 구한 비율로 입력합니다.
		}
	}
}
