// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "ABGameplayWidget.h"
#include "ABGamePlayResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGamePlayResultWidget : public UABGameplayWidget
{
	GENERATED_BODY()
	
public:
	void BindGameState(class AABGameState* GameState);
	// 게임 스테이트와 연결함수
protected:
	virtual void NativeConstruct() override;
	// 클래스 초기화
private:
	TWeakObjectPtr<class AABGameState> CurrentGameState;
	
};
