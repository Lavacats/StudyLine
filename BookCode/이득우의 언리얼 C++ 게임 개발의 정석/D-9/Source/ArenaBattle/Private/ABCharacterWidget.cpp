// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacterWidget.h"

void UABCharacterWidget::BindCharacterStat(UABCharacterStatComponent * NewCharacterStat) {

	ABCHECK(nullptr != NewCharacterStat);
	// NewChaacterStat�� ���������� �о����� Ȯ���մϴ�.

	CurrentCharacterStat = NewCharacterStat;
	// ���� ĳ���� ������Ʈ�� NewCharacterStat�� �ֽ��ϴ�.

	//NewCharacterStat->OnHPChanged.AddLambda([this]()->void {
	//	if (CurrentCharacterStat.IsValid()) {
	//		ABLOG(Warning, TEXT("HPRadtio : %f"), CurrentCharacterStat->GetHPRatio());
	//		// CurrentCharacterStat�� ���������� �ҷ��Դٸ� CurrentCharacterStat�� HP������ �α׷� ����մϴ�.
	//	}
	//});

	NewCharacterStat->OnHPChanged.AddUObject(this, &UABCharacterWidget::UpdateHPWidget);
	//  NewCharacterStat�� UpdateHPWidget�� OnHpChanged �̺�Ʈ���� ����ǵ��� ���Ѵ�.
}

void UABCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Override�ž����Ƿ� �θ� ���� ��������ݴϴ�.
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBAR")));
	// HPProgressBar�� �ҷ��ɴϴ�.
	ABCHECK(nullptr != HPProgressBar);
	// ���α׷����ٸ� ���������� �ҷ��Դ��� üũ�մϴ�.
	UpdateHPWidget();
	// HP�ٸ� ������Ʈ�մϴ�.
}

void UABCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid()) {
		// CurrentCharacterStat �� �����ϰ�
		if (nullptr != HPProgressBar) {
			// HPProgressBar�� ���� ��
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
			// ���α׷������� Percetn�� CurrentCharacterStat���� ���� ������ �Է��մϴ�.
		}
	}
}
