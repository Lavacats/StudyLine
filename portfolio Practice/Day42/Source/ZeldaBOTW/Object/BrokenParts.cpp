// Fill out your copyright notice in the Description page of Project Settings.

#include "BrokenParts.h"


// Sets default values
ABrokenParts::ABrokenParts()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));
	RootComponent = DestructibleComponent;
	DestructibleComponent->SetSimulatePhysics(true);

	DestructibleComponent->SetCollisionProfileName(TEXT("BrokenObject"));
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

void ABrokenParts::setDestructibleComponentMesh(UDestructibleMesh * mesh)
{
	DestructibleComponent->SetDestructibleMesh(mesh);
}

void ABrokenParts::TakeDamage()
{
	ABLOG(Warning, TEXT("Damage!broken"));
	DestructibleComponent->ApplyDamage(10.0f,GetActorLocation(),FVector(0,0,0),10.0f);
}

