// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAnimInstance.h"
#include "EnemyCharacter.h"
#include "Weapon_Sword.h"
#include "P2PlayerController.h"
#include "P2PlayerState.h"
#include "PlayerCharacter.h"

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
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	AP2PlayerController* PController = Cast< AP2PlayerController>(PlayerController);
	AP2PlayerState* PlayerState = PController->getPlayerState();
	PlayerState->setCounterPossibility(true);
}

void UEnemyAnimInstance::AnimNotify_AttackEnd()
{
	AEnemyCharacter* EnmeyCharacter = Cast< AEnemyCharacter>(EnemyState->GetOwner());
	AWeapon_Sword* Weapon_Sword = Cast<AWeapon_Sword>(EnmeyCharacter->getWeapon());
	if (Weapon_Sword != nullptr) {
		Weapon_Sword->setHitPlayer(false);
		EnemyState->DelayTimer();
	}
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	AP2PlayerController* PController = Cast< AP2PlayerController>(PlayerController);
	AP2PlayerState* PlayerState = PController->getPlayerState();
	PlayerState->setCounterPossibility(false);
}

void UEnemyAnimInstance::AnimNotify_HurtEnd()
{
	EnemyState->setCurEnemyState(EnemyCharacterState::Enemy_IDLE);
}

void UEnemyAnimInstance::AnimNotify_ArrowShotEnd()
{
	AEnemyCharacter* EnmeyCharacter = Cast< AEnemyCharacter>(EnemyState->GetOwner());
	AWeapon_Sword* Weapon_Sword = Cast<AWeapon_Sword>(EnmeyCharacter->getWeapon());
	if (Weapon_Sword != nullptr) {
		Weapon_Sword->setHitPlayer(false);
		EnemyState->DelayTimer();
		EnmeyCharacter->ShootArrow();
	}
}

