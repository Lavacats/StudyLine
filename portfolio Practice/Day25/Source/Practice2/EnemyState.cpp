// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyState.h"
#include "EnemyCharacter.h"

UEnemyState::UEnemyState()
{
	PrimaryComponentTick.bCanEverTick = true;

	EnemyCharacterWeaponType = EnemyWeaponType::Weapon_Sword;
	curEnemyState = EnemyCharacterState::Enemy_IDLE;

	enemyMaxHp = 10.0;
	enemyCurHp = enemyMaxHp;
	
	IdleNumber = 1;
	IdleRange = 100.0f;
	AttackRange =100.0f;
	MaxAttackRange = 800.0f;
	EnemyMaxRange = false;
	OnBattle = false;
	InAttackRange=false;
	hasWeapon=false;
	AttackDelay = false;
}

void UEnemyState::BeginPlay()
{
	Super::BeginPlay();
	switch (EnemyCharacterWeaponType){
	case EnemyWeaponType::Weapon_Sword:
		AttackRange = 100.0f;
		break;
	case EnemyWeaponType::Weapon_Bow:
		AttackRange = 400.0f;
		break;
	}
}

void UEnemyState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	CurrentChracterSpeed = GetOwner()->GetVelocity().Size();

	if (curEnemyState != EnemyCharacterState::Enemy_DEATH) {
		if (curEnemyState != EnemyCharacterState::Enemy_HURT) {
			if (CurrentChracterSpeed > 1.0f) {
				curEnemyState = EnemyCharacterState::Enemy_RUN;
			}
			else if (OnBattle && InAttackRange && !AttackDelay && hasWeapon && !EnemyMaxRange) {
				curEnemyState = EnemyCharacterState::Enemy_ATTACK;
				AEnemyCharacter* OnwerCharacter = Cast<AEnemyCharacter>(GetOwner());
				if (OnwerCharacter != nullptr) {
					FVector Xrotator = (GetOwner()->GetActorLocation() - OnwerCharacter->getPlayerCharacter()->GetActorLocation());
					GetOwner()->SetActorRelativeRotation(FRotator(0, Xrotator.Rotation().Yaw,0) + FRotator(0, 180.0f, 0));
				}
			}
			else {
				curEnemyState = EnemyCharacterState::Enemy_IDLE;
			}
		}
	}
}

void UEnemyState::HurtEnemy()
{
	if (enemyCurHp > 1) {
		if (curEnemyState != EnemyCharacterState::Enemy_HURT) {
			enemyCurHp--;
			curEnemyState = EnemyCharacterState::Enemy_HURT;
		}
	}
	else {
		curEnemyState = EnemyCharacterState::Enemy_DEATH;
	}
}

void UEnemyState::AttackDelayFuncition()
{
	AttackDelay = false;
	GetWorld()->GetTimerManager().ClearTimer(AttackDelayTimerHandler);
}

void UEnemyState::DelayTimer()
{
	AttackDelay = true;
	curEnemyState = EnemyCharacterState::Enemy_IDLE;
	GetWorld()->GetTimerManager().SetTimer(AttackDelayTimerHandler, this, &UEnemyState::AttackDelayFuncition, 1.0f, true,1.5f);

}

