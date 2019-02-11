// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWeapon.h"

// Sets default values
APlayerWeapon::APlayerWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;
	ArrowBag = CreateDefaultSubobject<AActor>(TEXT("ArrowBag"));
	Bow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_BOW(TEXT("/Game/OBJECT/Bow/Bow/Travellers_Bow.Travellers_Bow"));
	if (SK_BOW.Succeeded()) {
		Bow->SetStaticMesh(SK_BOW.Object);
	}
	static ConstructorHelpers::FObjectFinder<AActor>SK_ARROW_BAG(TEXT("/Game/OBJECT/Bow/BOWBag/ArrowBag.ArrowBag_C"));
	if (SK_ARROW_BAG.Succeeded()) {
		//ArrowBag->SetStaticMesh(SK_ARROW_BAG.Object);
		ArrowBag = SK_ARROW_BAG.Object;
	}
	RootComponent = Bow;
	Bow->SetCollisionProfileName(TEXT("NoCollision"));
	Bow->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
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

