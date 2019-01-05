// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UABAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
	// �� Tick���� ȣ��Ǵ�, NativeUpdateAnimation�Լ�, 

	// Pawn���� instance�� ���� �ִϸ��̼��� �����ϴ� ���
	void SetPawnSpeed(float NewPawnSpeed);

	void PlayAttackMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;
	// 1. �����Ϳ��� ������ �����ϸ�
	// 2. �������Ʈ���� ���� �� �ְ�
	// 3. ī�װ��� Pawn
	// 4. private���� �����Ϳ��� ������ �� �ֵ��� Meta���
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;
	// 1. �����Ϳ��� ������ �����ϰ�
	// 2. �������Ʈ���� ���� �� �ְ�
	// 3. ī�װ��� Pawn
	// 4. private���� �����Ϳ��� ������ �� �ֵ��� Meta���

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
	// 1. �������Ʈ ũ���� ���赵������ ���������� VisibleDeaultsOnly�� ���
	// 2. �������Ʈ���� ���� �� �ִ�.
	// 3. ī�װ��� Attack
	// 4. private���� �����Ϳ��� ������ �� �ֵ��� Meta���

};
