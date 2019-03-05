// Fill out your copyright notice in the Description page of Project Settings.

#include "BrokenParts.h"


// Sets default values
ABrokenParts::ABrokenParts()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));
	DestructibleComponent->SetCollisionProfileName(TEXT("Broken"));
	DestructibleComponent->SetSimulatePhysics(true);
	DestructibleComponent->SetEnableGravity(true);
	DestructibleComponent->SetNotifyRigidBodyCollision(true);
}
// Called when the game starts or when spawned
void ABrokenParts::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrokenParts::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

