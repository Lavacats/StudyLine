// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Blueprint/UserWidget.h"
#include "ABChracterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABChracterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	void NextCharacter(bool bForward = true);
	// ���� ĳ���ͷ� �Ѿ�� �Լ�
	
	virtual void NativeConstruct() override;
	// ��ư�� �ʱ�ȭ�Լ�
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	int32 CurrentIndex;
	// ���� ĳ���� �ε���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	int32 MaxIndex;
	// �ε����� �ִ밪

	TWeakObjectPtr<USkeletalMeshComponent> TargetComponent;
	// Ÿ���� ���̷�Ż �޽� ������Ʈ

	UPROPERTY()
	class UButton* PrevButton;
	// �������� ���ư��� ��ư
	UPROPERTY()
	class UButton* NextButton;
	// �������� �Ѿ�� ��ư
	UPROPERTY()
	class UEditableTextBox* TextBox;
	// �ؽ�Ʈ����
	UPROPERTY()
	class UButton* ConfirmButton;
	// Ȯ�ι�ư

private:
	UFUNCTION()
	void OnPrevClicked();
	// ���� ��ư Ŭ�� �Լ�
	UFUNCTION()
	void OnNextClicked();
	// ���� ��ư Ŭ�� �Լ�
	UFUNCTION()
	void OnConfirmClicked();
	// Ȯ�� ��ư Ŭ�� �Լ�
};
