// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWeapon.h"
#include "Player/PlayerCharacter.h"
#include "Player/Controller/PlayerCharacterController.h"
#include "Player/PlayerUIWidget.h"

APlayerWeapon::APlayerWeapon()
{
 	PrimaryActorTick.bCanEverTick = true;
	Show_Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Show_Arrow"));
	Weapon_Sword = CreateDefaultSubobject<AWeapon_Equip>(TEXT("Weapon_Sword"));
	Weapon_Shield = CreateDefaultSubobject<AWeapon_Equip>(TEXT("Weapon_Shield"));
	Weapon_Bow = CreateDefaultSubobject<AWeapon_Equip>(TEXT("Weapon_Bow"));
	ArrowBag = CreateDefaultSubobject<AWeapon_Equip>(TEXT("ArrowBag"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_Arrow(TEXT("/Game/OBJECT/Bow/Arrow/WeaponArrow.WeaponArrow"));
	if (SK_Arrow.Succeeded()) {
		Show_Arrow->SetStaticMesh(SK_Arrow.Object);
	}

	Show_Arrow->SetCollisionProfileName(TEXT("NoCollision"));
	
	Weapon_Arrows = AWeapon_Arrow::StaticClass();
	ArrowCount = 6;
	WeaponSwordNum = -1;
	WeaponShieldNum = -1;
	WeaponBowNum = -1;

}

void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerWeapon::setWeaponComponent(E_Weapon Weapon, USkeletalMeshComponent * MeshComponent, const TCHAR * Socket)
{
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		Weapon_Bow->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		Weapon_Bow->getWeaponMesh()->SetVisibility(true);
		Weapon_Bow->getWeaponMesh()->SetCollisionProfileName(TEXT("Weapon"));
		if (IsValid(Weapon_Sword)) {
			Weapon_Sword->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, TEXT("LeftUpLegSocket"));
			Weapon_Sword->getWeaponMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			Weapon_Sword->getWeaponMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
			Weapon_Sword->getWeaponMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		}
		Weapon_Shield->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PlayerBackStorage"));
		Weapon_Shield->getWeaponMesh()->SetRelativeRotation(FRotator(180.0f, 180.0f, 0.0f));
		Weapon_Shield->getWeaponMesh()->SetRelativeLocation(FVector(20.0f, -2.0f, 0.0f));
		Weapon_Shield->getWeaponMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		break;
	case E_Weapon::Weapon_SWORD:
		Weapon_Bow->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PlayerBackStorage"));
		Weapon_Bow->getWeaponMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		if (IsValid(Weapon_Sword)) {
			Weapon_Sword->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, Socket);
			Weapon_Sword->getWeaponMesh()->SetRelativeRotation(FRotator(180.0f, 0.0f, -60.0f));
			Weapon_Sword->getWeaponMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
			Weapon_Sword->getWeaponMesh()->SetVisibility(true);
			Weapon_Sword->getWeaponMesh()->SetCollisionProfileName(TEXT("Weapon"));
		}
		break;
	case E_Weapon::Weapon_SHIELD:
		Weapon_Shield->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		Weapon_Shield->getWeaponMesh()->SetRelativeRotation(FRotator(140.0f, 120.0f, 80.0f));
		Weapon_Shield->getWeaponMesh()->SetRelativeLocation(FVector(10.0f, -10.0f, 10.0f));
		Weapon_Shield->getWeaponMesh()->SetVisibility(true);
		Weapon_Shield->getWeaponMesh()->SetCollisionProfileName(TEXT("Weapon"));
		break;
	case E_Weapon::Weapon_ARROW_BAG:
		ArrowBag->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		ArrowBag->getWeaponMesh()->SetRelativeLocation(FVector(0.0f, -2.0f, 0.0f));
		break;
	case E_Weapon::Weapon_None:
		if (IsValid(Weapon_Sword)) {
			Weapon_Sword->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepWorldTransform, TEXT("LeftUpLegSocket"));
			Weapon_Sword->getWeaponMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			Weapon_Sword->getWeaponMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
			Weapon_Sword->getWeaponMesh()->SetVisibility(true);
			Weapon_Sword->getWeaponMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		}
		Weapon_Shield->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PlayerBackStorage"));
		Weapon_Shield->getWeaponMesh()->SetRelativeRotation(FRotator(180.0f, 180.0f, 0.0f));
		Weapon_Shield->getWeaponMesh()->SetRelativeLocation(FVector(20.0f, -2.0f, 0.0f));
		Weapon_Shield->getWeaponMesh()->SetVisibility(true);
		Weapon_Shield->getWeaponMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		Weapon_Bow->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PlayerBackStorage"));
		Weapon_Bow->getWeaponMesh()->SetVisibility(true);
		Weapon_Bow->getWeaponMesh()->SetCollisionProfileName(TEXT("NoCollision"));
		ArrowBag->getWeaponMesh()->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BackWaistSocket"));
		ArrowBag->getWeaponMesh()->SetRelativeLocation(FVector(0.0f, -2.0f, 0.0f));

		break;
	}
}

void APlayerWeapon::FireArrow(FVector location, FRotator Rotation, FVector Forward)
{
	auto PlayerController = Cast< APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	auto PlayerUI = PlayerController->getPlayerCharacter()->getPlayerUI();

	PlayerUI->SetArrowCount(ArrowCount);

	if (ArrowCount > 0) {
		Show_Arrow->SetVisibility(false);
		ArrowCount--;
		auto Arrow = GetWorld()->SpawnActor<AWeapon_Arrow>(Weapon_Arrows, location, Rotation);
		if (Arrow) {
			FVector NewVelocity = Forward * 1000.0f;
			Arrow->setVelocity(NewVelocity);
			Arrow->setHitEnemy(true);
		}
	}
}

void APlayerWeapon::ShowArrowLocationRotation(FVector Location, FRotator Rotation, bool aimOnOFf)
{
	auto PlayerController = Cast< APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	auto PlayerUI = PlayerController->getPlayerCharacter()->getPlayerUI();

	PlayerUI->SetArrowCount(ArrowCount);

	if (aimOnOFf && ArrowCount > 0)
	{
		Show_Arrow->SetVisibility(aimOnOFf);
		Show_Arrow->SetRelativeLocation(Location);
		Show_Arrow->SetRelativeRotation(Rotation + FRotator(0.0f, -90.0f, 0.0f));
	}
}

bool APlayerWeapon::getWeaponVisible(E_Weapon Weapon)
{
	bool answer = false;
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		answer = Weapon_Bow->getWeaponMesh()->IsVisible();
		break;
	}
	return answer;
}

void APlayerWeapon::setWeaponVisible(E_Weapon Weapon, bool check)
{
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		Weapon_Bow->getWeaponMesh()->SetVisibility(check);
		break;
	}
}

void APlayerWeapon::ChangeWeapon(E_Weapon weaponType, bool Upvalue)
{
	switch (weaponType) {
		case E_Weapon::Weapon_SWORD:
			Weapon_Sword->getWeaponMesh()->SetVisibility(false);
			if (Upvalue) {
				if (Weapon_SwordList.Num() - 1 > WeaponSwordNum) {
					WeaponSwordNum++;
				}
				else {
					WeaponSwordNum = 0;
				}
			}
			else {
				if (Weapon_SwordList.Num() > 1) {
					if (WeaponSwordNum == 0) {
						WeaponSwordNum = Weapon_SwordList.Num() - 1;
					}
					else {
						WeaponSwordNum--;
					}
				}
			}
			Weapon_Sword = Weapon_SwordList[WeaponSwordNum % Weapon_SwordList.Num()];
			Weapon_Sword->getWeaponMesh()->SetCollisionProfileName(TEXT("PlayerWeapon"));
			Weapon_Sword->getWeaponMesh()->SetVisibility(true);
			break;
		case E_Weapon::Weapon_BOW:
			Weapon_Bow->getWeaponMesh()->SetVisibility(false);
			if (Upvalue) {
				if (Weapon_BowList.Num() - 1 > WeaponBowNum) {
					WeaponBowNum++;
				}
				else {
					WeaponBowNum = 0;
				}
			}
			else {
				if (Weapon_BowList.Num() > 1) {
					if (WeaponBowNum == 0) {
						WeaponBowNum = Weapon_BowList.Num() - 1;
					}
					else {
						WeaponBowNum--;
					}
				}
			}
			Weapon_Bow = Weapon_BowList[WeaponBowNum % Weapon_BowList.Num()];
			Weapon_Bow->getWeaponMesh()->SetCollisionProfileName(TEXT("PlayerWeapon"));
			Weapon_Bow->getWeaponMesh()->SetVisibility(true);
			break;
	}
}

void APlayerWeapon::AddSwordList(AWeapon_Equip * sword)
{
	Weapon_Sword->getWeaponMesh()->SetVisibility(false);
	Weapon_Sword = sword;
	Weapon_SwordList.Add(sword);
	WeaponSwordNum++;
}

void APlayerWeapon::AddBowdList(AWeapon_Equip * sword)
{
	Weapon_Bow->getWeaponMesh()->SetVisibility(false);
	Weapon_Bow = sword;
	Weapon_BowList.Add(sword);
	WeaponBowNum++;
}

void APlayerWeapon::AddShieldList(AWeapon_Equip * sword)
{
	Weapon_Shield->getWeaponMesh()->SetVisibility(false);
	Weapon_Shield = sword;
	Weapon_ShieldList.Add(sword);
	WeaponShieldNum ++;
}

void APlayerWeapon::AddArrowBagList(AWeapon_Equip * bag)
{
	ArrowBag = bag;
}

bool APlayerWeapon::checkParentComponent(E_Weapon Weapon, const TCHAR * Socket)
{
	bool answer = false;
	FName socketNameString;
	FName NameOfSocket = FName(Socket);
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		socketNameString = Weapon_Bow->getWeaponMesh()->GetAttachSocketName();
		if (socketNameString.IsEqual(NameOfSocket)){
			answer = true;
		}
		break;
	case E_Weapon::Weapon_SWORD:
		if (IsValid(Weapon_Sword)) {
			socketNameString = Weapon_Sword->getWeaponMesh()->GetAttachSocketName();
			if (Socket == socketNameString) {
				answer = true;
			}
		}
		break;
	case E_Weapon::Weapon_SHIELD:
		socketNameString = Weapon_Shield->getWeaponMesh()->GetAttachSocketName();
		if (Socket == socketNameString) {
			answer = true;
		}
		break;
	}
	return answer;
}

void APlayerWeapon::AddArrow()
{
	auto PlayerController = Cast< APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	auto PlayerCharacter =PlayerController->getPlayerCharacter();
	PlayerCharacter->getPlayerUI()->PrintMessageBox("Get 'Arrow x1'");
	ArrowCount++;
}
