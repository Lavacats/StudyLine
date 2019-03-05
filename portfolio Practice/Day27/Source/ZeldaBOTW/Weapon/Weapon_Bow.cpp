// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Bow.h"


// Sets default values
AWeapon_Bow::AWeapon_Bow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowMesh"));
}

// Called when the game starts or when spawned
void AWeapon_Bow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon_Bow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon_Bow::setShieldMesh(const TCHAR * ShieldMeshText)
{
	UStaticMesh* ReadBowMesh = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, ShieldMeshText));
	if (ReadBowMesh) {
		BowMesh->SetStaticMesh(ReadBowMesh);
	}
}

