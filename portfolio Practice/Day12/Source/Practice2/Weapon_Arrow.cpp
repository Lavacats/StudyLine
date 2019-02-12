// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Arrow.h"

// Sets default values
AWeapon_Arrow::AWeapon_Arrow()
{
 	PrimaryActorTick.bCanEverTick = false;
	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_ARROW(TEXT("/Game/OBJECT/Bow/Arrow/WeaponArrow.WeaponArrow"));
	if (SK_ARROW.Succeeded()) {
		ArrowMesh->SetStaticMesh(SK_ARROW.Object);
	}
	//ArrowMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	RootComponent = ArrowMesh;
}

// Called when the game starts or when spawned
void AWeapon_Arrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

