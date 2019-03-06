// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacterState.h"
#include "Enemy/EnemyCharacter.h"

// Sets default values for this component's properties
UEnemyCharacterState::UEnemyCharacterState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	EnemyCharacterWeaponType = EnemyWeaponType::Weapon_Sword;
	curEnemyState = EnemyState::Enemy_IDLE;

	enemyMaxHp = 10.0;
	enemyCurHp = enemyMaxHp;

	IdleNumber = 1;
	IdleRange = 100.0f;
	AttackRange = 100.0f;
	MaxAttackRange = 800.0f;
	EnemyMaxRange = false;
	OnBattle = false;
	InAttackRange = false;
	hasWeapon = false;
	AttackDelay = false;
	// ...
}


// Called when the game starts
void UEnemyCharacterState::BeginPlay()
{
	Super::BeginPlay();
	switch (EnemyCharacterWeaponType) {
	case EnemyWeaponType::Weapon_Sword:
		AttackRange = 100.0f;
		break;
	case EnemyWeaponType::Weapon_Bow:
		AttackRange = 400.0f;
		break;
	}
	// ...
	
}


// Called every frame
void UEnemyCharacterState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	CurrentChracterSpeed = GetOwner()->GetVelocity().Size();

	if (curEnemyState != EnemyState::Enemy_DEATH) {
		if (curEnemyState != EnemyState::Enemy_HURT) {
			if (CurrentChracterSpeed > 1.0f) {
				curEnemyState = EnemyState::Enemy_RUN;
			}
			else if (OnBattle && InAttackRange && !AttackDelay && hasWeapon && !EnemyMaxRange) {
				curEnemyState = EnemyState::Enemy_ATTACK;
				AEnemyCharacter* OnwerCharacter = Cast<AEnemyCharacter>(GetOwner());
				if (OnwerCharacter != nullptr) {
					FVector Xrotator = (GetOwner()->GetActorLocation() - OnwerCharacter->getPlayerCharacter()->GetActorLocation());
					GetOwner()->SetActorRelativeRotation(FRotator(0, Xrotator.Rotation().Yaw, 0) + FRotator(0, 180.0f, 0));
				}
			}
			else {
				curEnemyState = EnemyState::Enemy_IDLE;
			}
		}
	}
}

void UEnemyCharacterState::HurtEnemy()
{
	if (enemyCurHp > 1) {
		if (curEnemyState != EnemyState::Enemy_HURT) {
			enemyCurHp--;
			curEnemyState = EnemyState::Enemy_HURT;
		}
	}
	else {
		curEnemyState = EnemyState::Enemy_DEATH;
	}

}

void UEnemyCharacterState::AttackDelayFuncition()
{
	AttackDelay = false;
	GetWorld()->GetTimerManager().ClearTimer(AttackDelayTimerHandler);
}

void UEnemyCharacterState::DelayTimer()
{
	AttackDelay = true;
	curEnemyState = EnemyState::Enemy_IDLE;
	GetWorld()->GetTimerManager().SetTimer(AttackDelayTimerHandler, this, &UEnemyCharacterState::AttackDelayFuncition, 1.0f, true, 1.5f);

}

