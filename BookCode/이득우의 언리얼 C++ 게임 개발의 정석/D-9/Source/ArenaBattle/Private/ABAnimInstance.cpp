// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	// IsInAir�� �ʱⰪ���� false�� �ش�.
	IsDead = false;
	// IsDead�� �ʱⰪ���� false�� �ش�

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

	if (!::IsValid(Pawn))return;
	// Pawn�� ���������ʴ� �ٸ� �������� �ʴ´�.

	if (!IsDead) {
		// ���� �ʾҴٸ� �ִϸ��̼��� ��� ����մϴ�.

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
	ABCHECK(!IsDead);
	// �÷��̾��� ������θ� üũ�մϴ�.
	Montage_Play(AttackMontage, 1.0f);
	// ��Ÿ��(Montage)�� ����մϴ�.
}

void UABAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	ABCHECK(!IsDead);
	// �÷��̾��� ������θ� üũ�մϴ�.
	ABCHECK(Montage_IsPlaying(AttackMontage));
	// ���� ��Ÿ�ְ� ��������� Ȯ���մϴ�.
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
	// ���� ��Ÿ�ָ� �޾ƿ� �̸� (NewSectioN)�� ����� ���� �������� �ѱ�ϴ�.
}

void UABAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
	//BroadCast�� Delegate�� ����� �����Լ��� ���ÿ� ȣ���� �� ����ϴ� �Լ��Դϴ�
}

void UABAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
	//BroadCast�� Delegate�� ����� �����Լ��� ���ÿ� ȣ���� �� ����ϴ� �Լ��Դϴ�
}

FName UABAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	ABCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"),Section));
	// ���� ��Ÿ���� Section�� �̸��� ����ϰ� ��ȯ�մϴ�.
}
