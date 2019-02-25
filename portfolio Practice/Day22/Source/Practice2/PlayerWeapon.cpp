// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWeapon.h"
#include "PlayerCharacter.h"
#include "P2PlayerController.h"
#include "PlayerUIWidget.h"

APlayerWeapon::APlayerWeapon()
{
 	PrimaryActorTick.bCanEverTick = true;

	Show_Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Show_Arrow"));
	Weapon_Sword = CreateDefaultSubobject<AWeapon_Sword>(TEXT("Weapon_Sword"));
	Weapon_Shield = CreateDefaultSubobject<AWeapon_Shield>(TEXT("Weapon_Shield"));
	Weapon_Bow = CreateDefaultSubobject<AWeapon_Bow>(TEXT("Weapon_Bow"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_Arrow(TEXT("/Game/OBJECT/Bow/Arrow/WeaponArrow.WeaponArrow"));
	if (SK_Arrow.Succeeded()) {
		Show_Arrow->SetStaticMesh(SK_Arrow.Object);
	}
	static ConstructorHelpers::FObjectFinder<UClass>SK_ARROW_BAG(TEXT("/Game/OBJECT/Bow/BOWBag/ArrowBag.ArrowBag_C"));
	if (SK_ARROW_BAG.Succeeded ()) {
		ArrowBagBP = SK_ARROW_BAG.Object;
	}	

	Show_Arrow->SetCollisionProfileName(TEXT("NoCollision"));
	Weapon_Shield->getShieldMesh()->SetCollisionProfileName(TEXT("NeCollision"));
	Weapon_Arrows = AWeapon_Arrow::StaticClass();
	Weapon_Sword_Class = AWeapon_Sword::StaticClass();
	Weapon_ShieldClass = AWeapon_Shield::StaticClass();
	Weapon_BowClass = AWeapon_Bow::StaticClass();
	ArrowCount = 6;
}

void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	ArrowBag = GetWorld()->SpawnActor<AActor>(ArrowBagBP, FVector::ZeroVector, FRotator::ZeroRotator);
	
	Weapon_Sword = GetWorld()->SpawnActor<AWeapon_Sword>(Weapon_Sword_Class, FVector::ZeroVector, FRotator::ZeroRotator);
	Weapon_Sword->setSwordMesh(
		TEXT("/Game/OBJECT/Sword/sword.sword"),
		TEXT("/Game/OBJECT/Sword/Sword_Sheath.Sword_Sheath")
	);
	Weapon_Sword->getSwordMesh()->SetCollisionProfileName(TEXT("PlayerWeapon"));

	Weapon_Shield = GetWorld()->SpawnActor<AWeapon_Shield>(Weapon_ShieldClass, FVector::ZeroVector, FRotator::ZeroRotator);
	Weapon_Shield->setShieldMesh(TEXT("/Game/OBJECT/Shield/Deku_Shield_model.Deku_Shield_model"));
	Weapon_Shield->getShieldMesh()->SetCollisionProfileName(TEXT("PlayerWeapon"));

	Weapon_Bow = GetWorld()->SpawnActor<AWeapon_Bow>(Weapon_BowClass, FVector::ZeroVector, FRotator::ZeroRotator);
	Weapon_Bow->setShieldMesh(TEXT("/Game/OBJECT/Bow/Bow/Travellers_Bow.Travellers_Bow"));
	Weapon_Bow->getBowMesh()->SetCollisionProfileName(TEXT("PlayerWeapon"));
}

void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerWeapon::setWeaponComponent(E_Weapon Weapon, USkeletalMeshComponent* MeshComponent, const TCHAR * Socket)
{
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		Weapon_Bow->getBowMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		Weapon_Sword->getSwordMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftUpLegSocket"));
	
		Weapon_Shield->getShieldMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PlayerBackStorage"));
		Weapon_Shield->getShieldMesh()->SetRelativeScale3D(FVector(0.015f, 0.015f, 0.015f));
		Weapon_Shield->getShieldMesh()->SetRelativeRotation(FRotator(180.0f, 180.0f, 0.0f));
		Weapon_Shield->getShieldMesh()->SetRelativeLocation(FVector(20.0f,-2.0f, 0.0f));

		Weapon_Sword->getSwordMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		Weapon_Sword->getSwordMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
		break;
	case E_Weapon::Weapon_SWORD:
		Weapon_Bow->getBowMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PlayerBackStorage"));
		Weapon_Sword->getSwordMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);

		Weapon_Sword->getSwordMesh()->SetRelativeRotation(FRotator(180.0f,0.0f,-60.0f));
		Weapon_Sword->getSwordMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		break;
	case E_Weapon::Weapon_SHIELD:
		Weapon_Shield->getShieldMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		Weapon_Shield->getShieldMesh()->SetRelativeScale3D(FVector(0.015f, 0.015f, 0.015f));
		Weapon_Shield->getShieldMesh()->SetRelativeRotation(FRotator(140.0f, 120.0f, 80.0f));
		Weapon_Shield->getShieldMesh()->SetRelativeLocation(FVector(10.0f, -10.0f, 10.0f));
		break;
	case E_Weapon::Weapon_ARROW_BAG:
		ArrowBag->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		ArrowBag->SetActorRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
		ArrowBag->SetActorRelativeLocation(FVector(0.0f, -2.0f, 0.0f));
		break;
	case E_Weapon::Weapon_SWORD_SHEATH:
		Weapon_Sword->getSwordSheathMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		Weapon_Sword->getSwordSheathMesh()->SetRelativeLocation(FVector(0.0f, 20.0f, -10.0f));
		break;
	case E_Weapon::Weapon_None:
		Weapon_Sword->getSwordMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftUpLegSocket"));

		Weapon_Sword->getSwordMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		Weapon_Sword->getSwordMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
		Weapon_Shield->getShieldMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PlayerBackStorage"));
		Weapon_Shield->getShieldMesh()->SetRelativeScale3D(FVector(0.015f, 0.015f, 0.015f));
		Weapon_Shield->getShieldMesh()->SetRelativeRotation(FRotator(180.0f, 180.0f, 0.0f));
		Weapon_Shield->getShieldMesh()->SetRelativeLocation(FVector(20.0f, -2.0f, 0.0f));

		break;
	}
}

bool APlayerWeapon::getWeaponVisible(E_Weapon Weapon)
{
	bool answer = false;
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		answer = Weapon_Bow->getBowMesh()->IsVisible();
		break;
	}
	return answer;
}

void APlayerWeapon::setWeaponVisible(E_Weapon Weapon, bool check)
{
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		Weapon_Bow->getBowMesh()->SetVisibility(check);
		break;
	}
}

bool APlayerWeapon::checkParentComponent(E_Weapon Weapon, const TCHAR * Socket)
{
	bool answer = false;
	FName socketNameString;

	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		socketNameString = Weapon_Bow->getBowMesh()->GetAttachSocketName();
		if (Socket == socketNameString) {
			answer = true;
		}
		break;
	case E_Weapon::Weapon_SWORD:
		socketNameString = Weapon_Sword->getSwordMesh()->GetAttachSocketName();
		if (Socket == socketNameString) {
			answer = true;
		}
		break;
	case E_Weapon::Weapon_SHIELD:
		socketNameString = Weapon_Shield->getShieldMesh()->GetAttachSocketName();
		if (Socket == socketNameString) {
			answer = true;
		}
		break;
	}
	return answer;
}

void APlayerWeapon::FireArrow(FVector location, FRotator Rotation, FVector Forward)
{
	if (ArrowCount > 0) {
		Show_Arrow->SetVisibility(false);
		ArrowCount--;
		auto Arrow = GetWorld()->SpawnActor<AWeapon_Arrow>(Weapon_Arrows, location, Rotation);
		if (Arrow) {
			FVector NewVelocity = Forward * 1000.0f;
			Arrow->setVelocity(NewVelocity);
		}
		auto PlayerController = Cast< AP2PlayerController>(GetWorld()->GetFirstPlayerController());
		auto PlayerUI = PlayerController->getPlayerCharacter()->getPlayerCamera()->getPlayerUI();

		PlayerUI->SetArrowCount(ArrowCount);
	}
}

void APlayerWeapon::ShowArrowLocationRotation(FVector Location, FRotator Rotation, bool aimOnOFf)
{
	if (aimOnOFf && ArrowCount>0)
	{
		Show_Arrow->SetVisibility(aimOnOFf);
		Show_Arrow->SetRelativeLocation(Location);
		Show_Arrow->SetRelativeRotation(Rotation + FRotator(0.0f,-90.0f,0.0f));
	}
}
