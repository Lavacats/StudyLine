// Fill out your copyright notice in the Description page of Project Settings.

#include "BrokenObject.h"
#include "Engine.h"
#include "Weapon_Sword.h"
// Sets default values
ABrokenObject::ABrokenObject()
{
 	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));
	StaticComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticComponent"));
	DropItemMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("DropItemMesh"));
	DropItem = CreateDefaultSubobject<AActor>(TEXT("DropItem"));
	DestructibleComponent->SetNotifyRigidBodyCollision(true);

	RootComponent = StaticComponent;
	StaticComponent->SetNotifyRigidBodyCollision(true);
	DestructibleComponent->SetupAttachment(StaticComponent);
	IsDestroyed = false;

	//DestructibleComponent->SetVisibility(false);
	MaxHealth = 3.f;
	DestructibleComponent->SetCollisionProfileName(TEXT("NoCollision"));
	DestructibleComponent->SetSimulatePhysics(false);
	DestructibleComponent->SetCollisionProfileName(TEXT("BrokenObject"));
	StaticComponent->SetCollisionProfileName(TEXT("Broken"));
	StaticComponent->ComponentTags.Add(FName("ExtraObject"));
	DropItemClass = AActor::StaticClass();
}

void ABrokenObject::BeginPlay()
{
	Super::BeginPlay();

	StaticComponent->OnComponentHit.AddDynamic(this, &ABrokenObject::OnHitComponent);
	CurrentHealth = MaxHealth;
}

void ABrokenObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABrokenObject::Broken()
{
	StaticComponent->SetSimulatePhysics(false);
	StaticComponent->SetCollisionProfileName(TEXT("NoCollision"));
	DestructibleComponent->SetRelativeLocation(StaticComponent->GetRelativeTransform().GetLocation());
	DestructibleComponent->SetSimulatePhysics(true);
	StaticComponent->SetVisibility(false);
	IsDestroyed = true;



	AActor* Item = GetWorld()->SpawnActor<AActor>(DropItemClass, StaticComponent->GetRelativeTransform().GetLocation(), FRotator::ZeroRotator);
	auto ItemClass = Cast< AWeapon_Sword>(Item);
	if (ItemClass != nullptr) {
		ItemClass->getSwordMesh()->SetStaticMesh(DropItemMesh);
	}
	//this->Destroy();
}

void ABrokenObject::setCharacterEquip(USkeletalMeshComponent * MeshComponent, const TCHAR * Socket)
{
	if (IsValid(StaticComponent)) {
		StaticComponent->SetSimulatePhysics(false);
		StaticComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
	}
}

void ABrokenObject::setObjectHPDamage()
{
	ABLOG(Warning, TEXT("DAMAGE"));
	CurrentHealth--;
	if (CurrentHealth < 1) {
		Broken();
	}
}

void ABrokenObject::setBrokenColiision(bool value)
{
	if (value) {
		DestructibleComponent->SetCollisionProfileName(TEXT("BrokenObject"));
	}
	else {
		DestructibleComponent->SetCollisionProfileName(TEXT("NoCollision"));
	}
}


void ABrokenObject::OnHitComponent(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (!IsDestroyed && OtherComp->ComponentHasTag("Weapon")){
		setObjectHPDamage();
	}
}

