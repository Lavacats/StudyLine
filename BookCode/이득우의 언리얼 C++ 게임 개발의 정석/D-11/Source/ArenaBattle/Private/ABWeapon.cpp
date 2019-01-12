// Fill out your copyright notice in the Description page of Project Settings.

#include "ABWeapon.h"


// Sets default values
AABWeapon::AABWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));
	// ���۷����� ���� ���⸦ ��������
	if (SK_WEAPON.Succeeded()) {
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
		// ���⸦ ���������� �ҷ��Դٸ� SkeletalMesh�� weaopon�� �����մϴ�.
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
	// �̹����� Weapon�� �浹�� ������� ���� ���̹Ƿ� NoCollision�� �����մϴ�.

	AttackRange = 150.0f;
	// ���� ���� 150
	AttackDamageMin = -2.5f;
	// �ּ� ���ݵ�����
	AttackDamageMax = 10.0f;
	// �ִ� ���� ������
	AttackModifierMin = 0.85f;
	// ȿ�� ���ݷ� �ּҰ�
	AttackModifierMax = 1.25;
	// ȿ�� ���ݷ� �ִ밪
}

float AABWeapon::GetAttackRange() const
{
	return AttackRange;
	// ���� ������ ��ȯ�޽��ϴ�.
}

float AABWeapon::GetAttackDamage() const
{
	return AttackDamage;
}

float AABWeapon::GetAttackModifier() const
{
	return AttackModifier;
}

// Called when the game starts or when spawned
void AABWeapon::BeginPlay()
{
	Super::BeginPlay();

	AttackDamage = FMath::RandRange(AttackDamageMin, AttackDamageMax);
	// AttackDamage�� �ּ� �������� �ִ� ���������� ������ ���� ������
	AttackModifier = FMath::RandRange(AttackModifierMin, AttackModifierMax);
	// AttackModifier�� �ּ� ȿ�� ���ܰ��� �ִ� ȿ�� ���ݰ��� ������ ���� ������.

	ABLOG(Warning, TEXT("Weapon Damage : %f, Modifier : %f"), AttackDamage, AttackModifier);
	// ���ظ� �ذ��� �α׷� ����մϴ�
}

// Called every frame
void AABWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

