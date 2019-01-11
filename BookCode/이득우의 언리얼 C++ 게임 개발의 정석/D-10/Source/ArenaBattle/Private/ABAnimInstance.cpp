// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	// IsInAir의 초기값으로 false를 준다.
	IsDead = false;
	// IsDead의 초기값으로 false를 준다

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

	if (!::IsValid(Pawn))return;
	// Pawn이 존재하지않는 다면 실행하지 않는다.

	if (!IsDead) {
		// 죽지 않았다면 애니메이션을 계속 재생합니다.

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
	ABCHECK(!IsDead);
	// 플레이어의 사망여부를 체크합니다.
	Montage_Play(AttackMontage, 1.0f);
	// 몽타주(Montage)를 재생합니다.
}

void UABAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	ABCHECK(!IsDead);
	// 플레이어의 사망여부를 체크합니다.
	ABCHECK(Montage_IsPlaying(AttackMontage));
	// 현재 몽타주가 재생중인지 확인합니다.
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
	// 현재 몽타주를 받아온 이름 (NewSectioN)을 사용해 다음 새션으로 넘깁니다.
}

void UABAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
	//BroadCast는 Delegate에 연결된 여러함수를 동시에 호출할 때 사용하는 함수입니다
}

void UABAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
	//BroadCast는 Delegate에 연결된 여러함수를 동시에 호출할 때 사용하는 함수입니다
}

FName UABAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	ABCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"),Section));
	// 현재 몽타주의 Section의 이름을 출력하고 반환합니다.
}
