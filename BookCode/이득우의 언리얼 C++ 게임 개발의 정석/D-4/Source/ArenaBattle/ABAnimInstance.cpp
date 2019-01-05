// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	// IsInAir의 초기값으로 false를 준다.

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Book/Animation/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded()) {
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	auto Pawn = TryGetPawnOwner();
	// 현재 Pawn의 정보를 가져오는 TryGetPawnOwner함수

	if (::IsValid(Pawn)) {
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		// Pawn이 있다면 Pawn의 속도(Velocity())를 가져온다.

		auto Character = Cast<ACharacter>(Pawn);
		if (Character) {
			IsInAir = Character->GetMovementComponent()->IsFalling();
			// InsInAIr은 Pawn의 IsFalling의 값을 가진다.
		}
	}

	// Pawn에서 instance를 통해 애니메이션을 조절하는 방법
	// Super::NativeUpdateAnimation(DeltaSeconds);
}

void UABAnimInstance::SetPawnSpeed(float NewPawnSpeed)
{ 
	CurrentPawnSpeed = NewPawnSpeed; 
}

void UABAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage)) {
		Montage_Play(AttackMontage, 1.0f);
		// 몽타주(Montage)를 재생합니다.
	}
}
