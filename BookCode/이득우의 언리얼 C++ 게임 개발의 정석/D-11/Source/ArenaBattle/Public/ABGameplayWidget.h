// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Blueprint/UserWidget.h"
#include "ABGameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	// �ʱ�ȭ �Լ�

	UFUNCTION()
	void OnResumeClicked();
	UFUNCTION()
	void OnReturnToTitleClicked();
	UFUNCTION()
	void OnRetryGameClicked();
	// ��ư Ŭ�� �Լ�

protected:
	UPROPERTY()
	class UButton* ResumeButton;
	UPROPERTY()
	class UButton* ReturnToTitleButton;
	UPROPERTY()
	class UButton* RetryGameButton;
	// ��ư ������
	
	
};
