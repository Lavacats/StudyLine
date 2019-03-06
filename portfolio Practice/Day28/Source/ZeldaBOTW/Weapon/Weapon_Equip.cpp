// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Equip.h"
#include "Enemy/EnemyCharacterState.h"
#include "Enemy/EnemyCharacter.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerCharacterState.h"
#include "Player/Controller/PlayerCharacterController.h"

AWeapon_Equip::AWeapon_Equip()
{
 	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	hitEnemy = false;
	hitPlayer = false;
	CurWeaponType = WeaponType::WeaponType_Sword;

	RootComponent = WeaponMesh;
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);

	WeaponMesh->SetCollisionProfileName(TEXT("Weapon"));
	WeaponMesh->ComponentTags.Add(FName("Weapon"));
	this->Tags.Add(FName("Weapon"));
}

void AWeapon_Equip::BeginPlay()
{
	Super::BeginPlay();
	WeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_Equip::WeaponCollision);

}

void AWeapon_Equip::WeaponCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("Enemy") && hitEnemy) {
		AEnemyCharacter* EnemyCharacter = Cast< AEnemyCharacter>(OtherComp->GetOwner());
		if (IsValid(EnemyCharacter)) {
			EnemyCharacter->getEnemyState()->setOnBattle(true);
			EnemyCharacter->Hurt();
		}
		hitEnemy = false;
	}
	else if (OtherComp->ComponentHasTag("PlayerCharacter") && hitPlayer) {
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		APlayerCharacterController* PController = Cast< APlayerCharacterController>(PlayerController);
		if (IsValid(PController)) {
			PController->PlayerHurt();
			hitPlayer = false;
		}
	}
}

void AWeapon_Equip::setCharacterEquip(USkeletalMeshComponent * MeshComponent, const TCHAR * Socket)
{
	if (IsValid(WeaponMesh)) {
		WeaponMesh->SetSimulatePhysics(false);
		WeaponMesh->SetCollisionProfileName(TEXT("Weapon"));
		WeaponMesh->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
	}
}

