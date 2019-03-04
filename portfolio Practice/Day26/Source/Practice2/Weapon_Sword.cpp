// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Sword.h"
#include "EnemyCharacter.h"
#include "EnemyState.h"
#include "PlayerCharacter.h"
#include "P2PlayerController.h"
#include "P2PlayerState.h"

// Sets default values
AWeapon_Sword::AWeapon_Sword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMesh"));
	SwordMesh_Sheath = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMesh_Sheath"));
	//SwordCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SwordCollision"));
	hitEnemy = false;
	hitPlayer = false;
	//SwordCollisionComponent->SetSimulatePhysics(false);
	//SwordCollisionComponent->SetEnableGravity(false);
	RootComponent= SwordMesh;

	SwordMesh->SetSimulatePhysics(true);
	SwordMesh->SetEnableGravity(true);

	//SwordCollisionComponent->SetupAttachment(SwordMesh);
	SwordMesh->SetCollisionProfileName(TEXT("Weapon"));
	//SwordCollisionComponent->SetCollisionProfileName(TEXT("Weapon"));
	SwordMesh->ComponentTags.Add(FName("Weapon"));
	
}

// Called when the game starts or when spawned
void AWeapon_Sword::BeginPlay()
{
	Super::BeginPlay();
	SwordMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_Sword::SwordCollision);

}

// Called every frame
void AWeapon_Sword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon_Sword::setSwordMesh(const TCHAR * SwordMeshText, const TCHAR * SwordSheathMeshText)
{
	UStaticMesh* ReadSwordMesh = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, SwordMeshText));
	if (ReadSwordMesh){
		SwordMesh->SetStaticMesh(ReadSwordMesh);
		
	}
	UStaticMesh* ReadSwordSheathMesh = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, SwordSheathMeshText));
	if (ReadSwordSheathMesh){
		SwordMesh_Sheath->SetStaticMesh(ReadSwordSheathMesh);
	}
	
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
		AP2PlayerController* PController = Cast< AP2PlayerController>(PlayerController);
		PController->PlayerHurt();
		hitPlayer = false;
	}
}

void AWeapon_Sword::setCharacterEquip(USkeletalMeshComponent * MeshComponent, const TCHAR * Socket, int charactorNum )
{
	if (charactorNum == 1) {
		if (IsValid(SwordMesh)) {
			SwordMesh->SetSimulatePhysics(false);
			SwordMesh->SetCollisionProfileName(TEXT("Weapon"));
			SwordMesh->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
		}
	}
}

