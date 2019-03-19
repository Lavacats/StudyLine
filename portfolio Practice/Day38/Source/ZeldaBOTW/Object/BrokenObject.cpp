// Fill out your copyright notice in the Description page of Project Settings.

#include "BrokenObject.h"
#include "Weapon/Weapon_Equip.h"

// Sets default values
ABrokenObject::ABrokenObject()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	StaticComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticComponent"));
	DropItemMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("DropItemMesh"));
	DropItem = CreateDefaultSubobject<AActor>(TEXT("DropItem"));

	RootComponent = StaticComponent;
	StaticComponent->SetNotifyRigidBodyCollision(true);
	IsDestroyed = false;
	carryOn = false;

	MaxHealth = 3.f;
	StaticComponent->SetCollisionProfileName(TEXT("BrokenObject"));
	StaticComponent->ComponentTags.Add(FName("ExtraObject"));
	DropItemClass = AActor::StaticClass();
	brokenParts = UDestructibleComponent::StaticClass();
	brokenPartsClass = ABrokenParts::StaticClass();
}

void ABrokenObject::OnHitComponent(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (!IsDestroyed && OtherComp->ComponentHasTag("Weapon")) {
		setObjectHPDamage();
	}
}

// Called when the game starts or when spawned
void ABrokenObject::BeginPlay()
{
	Super::BeginPlay();

	StaticComponent->OnComponentHit.AddDynamic(this, &ABrokenObject::OnHitComponent);
	CurrentHealth = MaxHealth;
}

// Called every frame
void ABrokenObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrokenObject::Broken()
{

	auto parts = GetWorld()->SpawnActor<ABrokenParts>(brokenPartsClass, GetActorLocation() ,StaticComponent->GetRelativeTransform().Rotator());
	if (IsValid(parts)) {
		ABLOG(Warning, TEXT("Spawn"));
		parts->setDestructibleComponentMesh(DestructibleMesh);
		//parts->SetActorRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		parts->TakeDamage();
	}
	StaticComponent->SetSimulatePhysics(false);
	StaticComponent->SetCollisionProfileName(TEXT("NoCollision"));
	StaticComponent->SetVisibility(false);
	IsDestroyed = true;

	//AActor* Item = GetWorld()->SpawnActor<AActor>(DropItemClass, StaticComponent->GetRelativeTransform().GetLocation(), FRotator::ZeroRotator);
	//auto ItemClass = Cast< AWeapon_Equip>(Item);
	//if (ItemClass != nullptr) {
	//	ItemClass->getWeaponMesh()->SetStaticMesh(DropItemMesh);
	//}
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
	CurrentHealth--;
	if (CurrentHealth < 1) {
		Broken();
	}
}

void ABrokenObject::setBrokenColiision(bool value)
{
	if (value) {
		StaticComponent->SetCollisionProfileName(TEXT("BrokenObject"));
		carryOn = false;
	}
	else {
		StaticComponent->SetCollisionProfileName(TEXT("Broken"));
		carryOn = true;
	}
}

