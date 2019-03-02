// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Shield.h"


// Sets default values
AWeapon_Shield::AWeapon_Shield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
}

// Called when the game starts or when spawned
void AWeapon_Shield::BeginPlay()
{
	Super::BeginPlay();
	ShieldMesh->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_Shield::ShieldCollision);

}

// Called every frame
void AWeapon_Shield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon_Shield::setShieldMesh(const TCHAR * ShieldMeshText)
{
	UStaticMesh* ReadShieldMesh = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, ShieldMeshText));
	if (ReadShieldMesh) {
		ShieldMesh->SetStaticMesh(ReadShieldMesh);
	}
}

void AWeapon_Shield::ShieldCollision(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

