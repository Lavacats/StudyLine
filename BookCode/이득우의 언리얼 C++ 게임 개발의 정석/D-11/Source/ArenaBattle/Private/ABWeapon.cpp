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
	// 레퍼런스를 통해 무기를 가져오면
	if (SK_WEAPON.Succeeded()) {
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
		// 무기를 성공적으로 불러왔다면 SkeletalMesh에 weaopon을 장착합니다.
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
	// 이번에는 Weapon을 충돌에 사용하지 않을 것이므로 NoCollision을 선언합니다.

	AttackRange = 150.0f;
	// 공격 범위 150
	AttackDamageMin = -2.5f;
	// 최소 공격데미지
	AttackDamageMax = 10.0f;
	// 최대 공격 데미지
	AttackModifierMin = 0.85f;
	// 효과 공격력 최소값
	AttackModifierMax = 1.25;
	// 효과 공격력 최대값
}

float AABWeapon::GetAttackRange() const
{
	return AttackRange;
	// 공격 범위를 반환받습니다.
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
	// AttackDamage는 최소 데미지와 최대 데미지값중 무작위 값을 가진다
	AttackModifier = FMath::RandRange(AttackModifierMin, AttackModifierMax);
	// AttackModifier는 최소 효과 공겨값과 최대 효과 굥격값중 무작위 값을 가진다.

	ABLOG(Warning, TEXT("Weapon Damage : %f, Modifier : %f"), AttackDamage, AttackModifier);
	// 피해를 준값을 로그로 출력합니다
}

// Called every frame
void AABWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

