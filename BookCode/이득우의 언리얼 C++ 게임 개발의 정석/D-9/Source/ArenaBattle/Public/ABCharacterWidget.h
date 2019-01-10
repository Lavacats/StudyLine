// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "ABCharacterStatComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "ABCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterStat(UABCharacterStatComponent* NewCharacterStat);
	// ĳ���� ������ �����ɴϴ�.

protected:
	virtual void NativeConstruct() override;
	// UI �ý����� �غ�Ǹ� ȣ��Ǵ� �Լ�
	// init �Ŀ� ����ǰ� begin���� ����Ǵ� PostInitializeComponents���� �߻��� ����� UI�� �ݿ������ʴ´�.
	// ���� ���������� NativeConstruct ���� ���������� ������Ʈ�Ѵ�.

	void UpdateHPWidget();
	// ���� ������Ʈ �Լ�

private:
	TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;
	// ��������(TWeakObjectPtr)�� ����� ������Ʈ�� �����մϴ�.

	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
