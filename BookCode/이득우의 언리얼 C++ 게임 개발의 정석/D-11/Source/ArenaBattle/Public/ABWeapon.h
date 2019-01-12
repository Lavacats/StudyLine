// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Actor.h"
#include "ABWeapon.generated.h"

UCLASS()
class ARENABATTLE_API AABWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABWeapon();

	float GetAttackRange() const;
	// 공격범위를 반환합니다.
	float GetAttackDamage() const;
	// 공격 데미지 값을 반환
	float GetAttackModifier() const;
	// 공격 효과치 속성을 반환
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

protected:
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Attack)
	float AttackRange;
	// 플레이어의 공격범위

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Attack)
	float AttackDamageMin;
	// 플레이어의 최소 공격력

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Attack)
	float AttackDamageMax;
	// 플레이어의 최대 데미지

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Attack)
	float AttackModifierMin;
	// 플레이어 효과치 공격력의 최소값

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Attack)
	float AttackModifierMax;
	// 플레이어 효과치 공격력의 최대값

	UPROPERTY(Transient,VisibleInstanceOnly, BluePrintReadWrite, Category = Attack)
	float AttackDamage;
	// 주는 데미지 값

	UPROPERTY(Transient, VisibleInstanceOnly, BluePrintReadWrite, Category = Attack)
	float AttackModifier;
	// 효과치 공격력의 값
};
