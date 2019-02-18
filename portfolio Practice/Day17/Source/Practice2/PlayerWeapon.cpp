// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWeapon.h"
#include "PlayerCharacter.h"
#include "P2PlayerController.h"
#include "PlayerUIWidget.h"
// Sets default values
APlayerWeapon::APlayerWeapon()
{
 	PrimaryActorTick.bCanEverTick = true;

	Bow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow"));
	Sword_Sheath = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword_Sheath"));
	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
	Show_Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Show_Arrow"));
	Shield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield"));
	//Bow->GetBodyInstance()->bLockXRotation = true;
	//Bow->GetBodyInstance()->bLockYRotation = true;
	//Bow->GetBodyInstance()->bLockZRotation = true;
	//Arrows = CreateDefaultSubobject<AWeapon_Arrow>(TEXT("Arrows"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_BOW(TEXT("/Game/OBJECT/Bow/Bow/Travellers_Bow.Travellers_Bow"));
	if (SK_BOW.Succeeded()) {
		Bow->SetStaticMesh(SK_BOW.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_Sword_Sheath(TEXT("/Game/OBJECT/Sword/Sword_Sheath.Sword_Sheath"));
	if (SK_Sword_Sheath.Succeeded()) {
		Sword_Sheath->SetStaticMesh(SK_Sword_Sheath.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_Sword(TEXT("/Game/OBJECT/Sword/sword.sword"));
	if (SK_Sword.Succeeded()) {
		Sword->SetStaticMesh(SK_Sword.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_Arrow(TEXT("/Game/OBJECT/Bow/Arrow/WeaponArrow.WeaponArrow"));
	if (SK_Arrow.Succeeded()) {
		Show_Arrow->SetStaticMesh(SK_Arrow.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_Shield(TEXT("/Game/OBJECT/Shield/Deku_Shield_model.Deku_Shield_model"));
	if (SK_Shield.Succeeded()) {
		Shield->SetStaticMesh(SK_Shield.Object);
	}	static ConstructorHelpers::FObjectFinder<UClass>SK_ARROW_BAG(TEXT("/Game/OBJECT/Bow/BOWBag/ArrowBag.ArrowBag_C"));
	if (SK_ARROW_BAG.Succeeded ()) {
		ArrowBagBP = SK_ARROW_BAG.Object;
	}	
	//RootComponent = Bow;
	Bow->SetCollisionProfileName(TEXT("NoCollision"));
	Sword->SetCollisionProfileName(TEXT("NoCollision"));
	Show_Arrow->SetCollisionProfileName(TEXT("NoCollision"));
	Shield->SetCollisionProfileName(TEXT("NeCollision"));
	Weapon_Arrows = AWeapon_Arrow::StaticClass();
	ArrowCount = 6;
}

void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	ArrowBag = GetWorld()->SpawnActor<AActor>(ArrowBagBP, FVector::ZeroVector, FRotator::ZeroRotator);

}

void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerWeapon::setWeaponComponent(E_Weapon Weapon, USkeletalMeshComponent* MeshComponent, const TCHAR * Socket)
{
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		Bow->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		Sword->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftUpLegSocket"));
		
		Shield->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PlayerBackStorage"));
		Shield->SetRelativeScale3D(FVector(0.015f, 0.015f, 0.015f));
		Shield->SetRelativeRotation(FRotator(180.0f, 180.0f, 0.0f));
		Shield->SetRelativeLocation(FVector(20.0f,-2.0f, 0.0f));

		Sword->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		Sword->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
		break;
	case E_Weapon::Weapon_SWORD:
		Bow->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("PlayerBackStorage"));
		Sword->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);

		Sword->SetRelativeRotation(FRotator(180.0f,0.0f,-60.0f));
		Sword->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		break;
	case E_Weapon::Weapon_SHIELD:
		Shield->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		Shield->SetRelativeScale3D(FVector(0.015f, 0.015f, 0.015f));
		Shield->SetRelativeRotation(FRotator(140.0f, 120.0f, 80.0f));
		Shield->SetRelativeLocation(FVector(10.0f, -10.0f, 10.0f));
		break;
	case E_Weapon::Weapon_ARROW_BAG:
		ArrowBag->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		ArrowBag->SetActorRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
		ArrowBag->SetActorRelativeLocation(FVector(0.0f, -2.0f, 0.0f));
		break;
	case E_Weapon::Weapon_SWORD_SHEATH:
		Sword_Sheath->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		Sword_Sheath->SetRelativeLocation(FVector(0.0f, 20.0f, -10.0f));
		break;
	}
}

bool APlayerWeapon::getWeaponVisible(E_Weapon Weapon)
{
	bool answer = false;
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		answer = Bow->IsVisible();
		break;
	}
	return answer;
}

void APlayerWeapon::setWeaponVisible(E_Weapon Weapon, bool check)
{
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		Bow->SetVisibility(check);
		break;
	}
}

bool APlayerWeapon::checkParentComponent(E_Weapon Weapon, const TCHAR * Socket)
{
	bool answer = false;
	FName socketNameString;

	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		socketNameString = Bow->GetAttachSocketName();
		if (Socket == socketNameString) {
			answer = true;
		}
		break;
	case E_Weapon::Weapon_SWORD:
		socketNameString = Sword->GetAttachSocketName();
		if (Socket == socketNameString) {
			answer = true;
		}
		break;
	case E_Weapon::Weapon_SHIELD:
		socketNameString = Shield->GetAttachSocketName();
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
