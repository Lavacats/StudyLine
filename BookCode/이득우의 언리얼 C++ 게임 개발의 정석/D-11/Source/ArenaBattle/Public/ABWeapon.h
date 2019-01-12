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
	// ���ݹ����� ��ȯ�մϴ�.
	float GetAttackDamage() const;
	// ���� ������ ���� ��ȯ
	float GetAttackModifier() const;
	// ���� ȿ��ġ �Ӽ��� ��ȯ
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
	// �÷��̾��� ���ݹ���

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Attack)
	float AttackDamageMin;
	// �÷��̾��� �ּ� ���ݷ�

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Attack)
	float AttackDamageMax;
	// �÷��̾��� �ִ� ������

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Attack)
	float AttackModifierMin;
	// �÷��̾� ȿ��ġ ���ݷ��� �ּҰ�

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Attack)
	float AttackModifierMax;
	// �÷��̾� ȿ��ġ ���ݷ��� �ִ밪

	UPROPERTY(Transient,VisibleInstanceOnly, BluePrintReadWrite, Category = Attack)
	float AttackDamage;
	// �ִ� ������ ��

	UPROPERTY(Transient, VisibleInstanceOnly, BluePrintReadWrite, Category = Attack)
	float AttackModifier;
	// ȿ��ġ ���ݷ��� ��
};
