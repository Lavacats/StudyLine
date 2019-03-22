// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_Shop.h"


// Sets default values
ANPC_Shop::ANPC_Shop()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NPCMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NPCMesh"));
}

// Called when the game starts or when spawned
void ANPC_Shop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC_Shop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC_Shop::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

