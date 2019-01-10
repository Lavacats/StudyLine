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
	// 캐릭터 스탯을 가져옵니다.

protected:
	virtual void NativeConstruct() override;
	// UI 시스템이 준비되면 호출되는 함수
	// init 후에 실행되고 begin전에 실행되는 PostInitializeComponents에서 발생한 명령은 UI에 반영되지않는다.
	// 현재 구조에서는 NativeConstruct 에서 위젯내용을 업데이트한다.

	void UpdateHPWidget();
	// 위젯 업데이트 함수

private:
	TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;
	// 약포인터(TWeakObjectPtr)을 사용해 컴포넌트를 참조합니다.

	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
