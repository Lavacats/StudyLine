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
	// 다음 캐릭터로 넘어가는 함수
	
	virtual void NativeConstruct() override;
	// 버튼의 초기화함수
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	int32 CurrentIndex;
	// 현재 캐릭터 인덱스

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	int32 MaxIndex;
	// 인덱스의 최대값

	TWeakObjectPtr<USkeletalMeshComponent> TargetComponent;
	// 타겟의 스켈레탈 메쉬 컴포넌트

	UPROPERTY()
	class UButton* PrevButton;
	// 이전으로 돌아가는 버튼
	UPROPERTY()
	class UButton* NextButton;
	// 다음으로 넘어가는 버튼
	UPROPERTY()
	class UEditableTextBox* TextBox;
	// 텍스트상자
	UPROPERTY()
	class UButton* ConfirmButton;
	// 확인버튼

private:
	UFUNCTION()
	void OnPrevClicked();
	// 이전 버튼 클릭 함수
	UFUNCTION()
	void OnNextClicked();
	// 다음 버튼 클릭 함수
	UFUNCTION()
	void OnConfirmClicked();
	// 확인 버튼 클릭 함수
};
