// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAnimInstance.h"
#include "Enemy/EnemyCharacter.h"
#include "Weapon/Weapon_Equip.h"
#include "Player/Controller/PlayerCharacterController.h"
#include "Player/PlayerCharacterState.h"
#include "Player/PlayerCharacter.h"

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
	AEnemyCharacter* EnmeyCharacter = Cast< AEnemyCharacter>(EnemyState->GetOwner());
	AWeapon_Equip* Weapon_Sword = Cast<AWeapon_Equip>(EnmeyCharacter->getWeapon());
	if (Weapon_Sword != nullptr) {
		Weapon_Sword->setHitPlayer(true);
	}
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	APlayerCharacterController* PController = Cast< APlayerCharacterController>(PlayerController);
	UPlayerCharacterState* PlayerState = PController->getPlayerState();
	PlayerState->setCounterPossibility(true);
}

void UEnemyAnimInstance::AnimNotify_AttackEnd()
{
	AEnemyCharacter* EnmeyCharacter = Cast< AEnemyCharacter>(EnemyState->GetOwner());
	AWeapon_Equip* Weapon_Sword = Cast<AWeapon_Equip>(EnmeyCharacter->getWeapon());
	if (Weapon_Sword != nullptr) {
		Weapon_Sword->setHitPlayer(false);
		EnemyState->DelayTimer();
	}
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	APlayerCharacterController* PController = Cast< APlayerCharacterController>(PlayerController);
	UPlayerCharacterState* PlayerState = PController->getPlayerState();
	PlayerState->setCounterPossibility(false);
}

void UEnemyAnimInstance::AnimNotify_HurtEnd()
{
	EnemyState->setCurEnemyState(EnemyState::Enemy_IDLE);
}

void UEnemyAnimInstance::AnimNotify_ArrowShotEnd()
{
	AEnemyCharacter* EnmeyCharacter = Cast< AEnemyCharacter>(EnemyState->GetOwner());
	AWeapon_Equip* Weapon_Sword = Cast<AWeapon_Equip>(EnmeyCharacter->getWeapon());
	if (Weapon_Sword != nullptr) {
		Weapon_Sword->setHitPlayer(false);
		EnemyState->DelayTimer();
		EnmeyCharacter->ShootArrow();
	}
}
