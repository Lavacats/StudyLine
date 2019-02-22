// Fill out your copyright notice in the Description page of Project Settings.

#include "BrokenObject.h"
#include "Engine.h"
// Sets default values
ABrokenObject::ABrokenObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));
	StaticComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticComponent"));
	DestructibleComponent->SetNotifyRigidBodyCollision(true);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	
	StaticComponent->SetupAttachment(BoxComponent);

	IsDestroyed = false;
	IsTriggerEnabled = false;

	MaxHealth = 3.f;

	DefaultDamage = 1.f;
	DefaultImpulse = 1.f;
	DestructibleComponent->SetSimulatePhysics(false);
	StaticComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ABrokenObject::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABrokenObject::Trigger);

	CurrentHealth = MaxHealth;
}

// Called every frame
void ABrokenObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrokenObject::Damage(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, __FUNCTION__);

	if (!IsDestroyed && OtherComp->ComponentHasTag("Weapon"))
	{


		CurrentHealth = CurrentHealth - 1.f;
		ABLOG(Warning, TEXT("Damage, HP : %f"), CurrentHealth);
		if (CurrentHealth <= 0.f)
		{
			ABLOG(Warning, TEXT("Death"));
			//ABLOG(Warning,(BoxComponent->GetCollisionProfileName()));
			BoxComponent->SetCollisionProfileName(TEXT("Weapon"));
			//ABLOG(Warning, (BoxComponent->GetCollisionProfileName()));
			DestructibleComponent->SetRelativeLocation(StaticComponent->GetComponentLocation());
			DestructibleComponent->SetVisibility(true);
			StaticComponent->SetVisibility(false);
			IsDestroyed = true;
			Destroy();
		}
	}
}

void ABrokenObject::Trigger(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, __FUNCTION__);

	if (!IsDestroyed && OtherComp->ComponentHasTag("Weapon"))
	{
		CurrentHealth = CurrentHealth - 1.f;

		BoxComponent->SetSimulatePhysics(false);
		BoxComponent->SetCollisionProfileName(TEXT("NoCollision"));

		DestructibleComponent->SetRelativeLocation(BoxComponent->GetRelativeTransform().GetLocation());
		DestructibleComponent->SetSimulatePhysics(true);

		StaticComponent->SetVisibility(false);
		IsDestroyed = true;
	}
}

void ABrokenObject::Destroy()
{
	//ABLOG(Warning, TEXT("Destroy"));
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, __FUNCTION__);
}