// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Sword.h"
#include "Enemy/EnemyCharacterState.h"
#include "Enemy/EnemyCharacter.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerCharacterState.h"
#include "Player/Controller/PlayerCharacterController.h"

AWeapon_Sword::AWeapon_Sword()
{
	PrimaryActorTick.bCanEverTick = true;
	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMesh"));
	SwordMesh_Sheath = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMesh_Sheath"));
	
	hitEnemy = false;
	hitPlayer = false;
	
	RootComponent = SwordMesh;

	SwordMesh->SetSimulatePhysics(true);
	SwordMesh->SetEnableGravity(true);

	SwordMesh->SetCollisionProfileName(TEXT("Weapon"));
	SwordMesh->ComponentTags.Add(FName("Weapon"));
}

void AWeapon_Sword::BeginPlay()
{
	Super::BeginPlay();
	SwordMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_Sword::SwordCollision);

}

void AWeapon_Sword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon_Sword::SwordCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("Enemy") && hitEnemy) {

		AEnemyCharacter* EnemyCharacter = Cast< AEnemyCharacter>(OtherComp->GetOwner());
		if (EnemyCharacter != nullptr) {
			EnemyCharacter->getEnemyState()->setOnBattle(true);
			EnemyCharacter->Hurt();
		}
		hitEnemy = false;
	}
	else if (OtherComp->ComponentHasTag("PlayerCharacter") && hitPlayer) {

		auto PlayerController = GetWorld()->GetFirstPlayerController();
		APlayerCharacterController* PController = Cast< APlayerCharacterController>(PlayerController);
		PController->PlayerHurt();
		hitPlayer = false;
	}
}

void AWeapon_Sword::setSwordMesh(const TCHAR * SwordMeshText, const TCHAR * SwordSheathMeshText)
{
	UStaticMesh* ReadSwordMesh = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, SwordMeshText));
	if (ReadSwordMesh) {
		SwordMesh->SetStaticMesh(ReadSwordMesh);

	}
	UStaticMesh* ReadSwordSheathMesh = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, SwordSheathMeshText));
	if (ReadSwordSheathMesh) {
		SwordMesh_Sheath->SetStaticMesh(ReadSwordSheathMesh);
	}
}

void AWeapon_Sword::setCharacterEquip(USkeletalMeshComponent * MeshComponent, const TCHAR * Socket, int charactorNum)
{
	if (charactorNum == 1) {
		if (IsValid(SwordMesh)) {
			SwordMesh->SetSimulatePhysics(false);
			SwordMesh->SetCollisionProfileName(TEXT("Weapon"));
			SwordMesh->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
		}
	}
}

