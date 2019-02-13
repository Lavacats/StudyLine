// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWeapon.h"

// Sets default values
APlayerWeapon::APlayerWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;

	Bow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow"));

	Bow->GetBodyInstance()->bLockXRotation = true;
	Bow->GetBodyInstance()->bLockYRotation = true;
	Bow->GetBodyInstance()->bLockZRotation = true;
	//Arrows = CreateDefaultSubobject<AWeapon_Arrow>(TEXT("Arrows"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_BOW(TEXT("/Game/OBJECT/Bow/Bow/Travellers_Bow.Travellers_Bow"));
	if (SK_BOW.Succeeded()) {
		Bow->SetStaticMesh(SK_BOW.Object);
	}
	static ConstructorHelpers::FObjectFinder<UClass>SK_ARROW_BAG(TEXT("/Game/OBJECT/Bow/BOWBag/ArrowBag.ArrowBag_C"));
	if (SK_ARROW_BAG.Succeeded ()) {
		ArrowBagBP = SK_ARROW_BAG.Object;
	}	
	
	RootComponent = Bow;
	Bow->SetCollisionProfileName(TEXT("NoCollision"));
	Weapon_Arrows = AWeapon_Arrow::StaticClass();
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
		break;
	case E_Weapon::Weapon_ARROW_BAG:
		ArrowBag->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		ArrowBag->SetActorRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
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
	FName socketNameString = Bow->GetAttachSocketName();
	FString valueString = socketNameString.ToString();
	switch (Weapon) {
	case E_Weapon::Weapon_BOW:
		if (Socket == socketNameString) {
			answer = true;
		}
		break;
	}
	return answer;
}

void APlayerWeapon::FireArrow(FVector location, FRotator Rotation, FVector Forward)
{
	auto Arrow = GetWorld()->SpawnActor<AWeapon_Arrow>(Weapon_Arrows, location, Rotation);
	if (Arrow) {
		FVector NewVelocity = Forward * 1000.0f;
		Arrow->setVelocity(NewVelocity);
	}
}



AWeapon_Arrow * APlayerWeapon::getArrow()
{
	static int32 ArrowSequence = 0;
	AWeapon_Arrow * sendArrow;
	if (Arrows.Num() < ArrowNum) {
		auto Arrow = GetWorld()->SpawnActor<AWeapon_Arrow>(FVector::ZeroVector, FRotator::ZeroRotator);
		Arrows.AddUnique(Arrow);
		ArrowSequence++;
		sendArrow = Arrow;
	}
	else {
		sendArrow=Arrows[ArrowSequence % ArrowNum];
		ArrowSequence++;
	}
	return sendArrow;
}

