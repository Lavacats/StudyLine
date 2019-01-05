// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	// IsInAir�� �ʱⰪ���� false�� �ش�.

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Book/Animation/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded()) {
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	auto Pawn = TryGetPawnOwner();
	// ���� Pawn�� ������ �������� TryGetPawnOwner�Լ�

	if (::IsValid(Pawn)) {
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		// Pawn�� �ִٸ� Pawn�� �ӵ�(Velocity())�� �����´�.

		auto Character = Cast<ACharacter>(Pawn);
		if (Character) {
			IsInAir = Character->GetMovementComponent()->IsFalling();
			// InsInAIr�� Pawn�� IsFalling�� ���� ������.
		}
	}

	// Pawn���� instance�� ���� �ִϸ��̼��� �����ϴ� ���
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
		// ��Ÿ��(Montage)�� ����մϴ�.
	}
}
