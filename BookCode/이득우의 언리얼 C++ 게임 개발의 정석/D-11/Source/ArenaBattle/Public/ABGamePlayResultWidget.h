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
	// ���� ������Ʈ�� �����Լ�
protected:
	virtual void NativeConstruct() override;
	// Ŭ���� �ʱ�ȭ
private:
	TWeakObjectPtr<class AABGameState> CurrentGameState;
	
};
