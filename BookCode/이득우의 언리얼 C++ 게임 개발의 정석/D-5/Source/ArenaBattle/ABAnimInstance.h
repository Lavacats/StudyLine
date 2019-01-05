// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
// 함수를 DELEGATE에 연결 한다
// 여러개의 함수가 동시에 등록되도록 멀티캐스트로 선언한다
// 멀티 캐스트에 등록된 모든 함수를 호출하는 멀티캐스트 델리게이트 명령은 Broadcast다

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
	// 매 Tick마다 호출되는, NativeUpdateAnimation함수, 

	// Pawn에서 instance를 통해 애니메이션을 조절하는 방법
	void SetPawnSpeed(float NewPawnSpeed);

	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);
	// 어택 몽타주에서 다음 세선으로 넘어가는 함수

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	// Delegate에서 호출할 함수

private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();
	// 노티파이(애니메이션, 몽타주 도중 일정 구간에서 호출되는 함수)

	UFUNCTION()
	void AnimNotify_NextAttackCheck();
	// 애니메이션 노티파이를 다음 Attack으로 넘어가는지 체크한다

	FName GetAttackMontageSectionName(int32 Section);
	// 현재 Section의 Name을 가져온다.

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;
	// 1. 에디터에서 수정이 가능하며
	// 2. 블루프린트에서 읽을 수 있고
	// 3. 카테고리는 Pawn
	// 4. private지면 에디터에서 접근할 수 있도록 Meta사용
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;
	// 1. 에디터에서 수정이 가능하고
	// 2. 블루프린트에서 읽을 수 있고
	// 3. 카테고리는 Pawn
	// 4. private지면 에디터에서 접근할 수 있도록 Meta사용

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
	// 1. 블루프린트 크래스 설계도에서만 보여지도록 VisibleDeaultsOnly를 사용
	// 2. 블루프린트에서 읽을 수 있다.
	// 3. 카테고리는 Attack
	// 4. private지만 에디터에서 접근할 수 있도록 Meta사용

};
