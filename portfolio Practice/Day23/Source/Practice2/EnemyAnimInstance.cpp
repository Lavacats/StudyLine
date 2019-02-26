// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAnimInstance.h"
#include "EnemyCharacter.h"
#include "Weapon_Sword.h"
UEnemyAnimInstance::UEnemyAnimInstance()
{
}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UEnemyAnimInstance::AnimNotify_AttackStart()
{
	AEnemyCharacter* EnmeyCharacter=Cast< AEnemyCharacter>(EnemyState->GetOwner());
	AWeapon_Sword* Weapon_Sword = Cast<AWeapon_Sword>(EnmeyCharacter->getWeapon());
	if (Weapon_Sword != nullptr) {
		Weapon_Sword->setHitPlayer(true);
	}
}

void UEnemyAnimInstance::AnimNotify_AttackEnd()
{
	AEnemyCharacter* EnmeyCharacter = Cast< AEnemyCharacter>(EnemyState->GetOwner());
	AWeapon_Sword* Weapon_Sword = Cast<AWeapon_Sword>(EnmeyCharacter->getWeapon());
	if (Weapon_Sword != nullptr) {
		Weapon_Sword->setHitPlayer(false);
		EnemyState->DelayTimer();
	}
}

void UEnemyAnimInstance::AnimNotify_HurtEnd()
{
	EnemyState->setCurEnemyState(EnemyCharacterState::Enemy_IDLE);
}
