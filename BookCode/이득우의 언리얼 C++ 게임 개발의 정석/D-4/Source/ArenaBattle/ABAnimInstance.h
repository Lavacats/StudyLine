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
	// 매 Tick마다 호출되는, NativeUpdateAnimation함수, 

	// Pawn에서 instance를 통해 애니메이션을 조절하는 방법
	void SetPawnSpeed(float NewPawnSpeed);

	void PlayAttackMontage();

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
