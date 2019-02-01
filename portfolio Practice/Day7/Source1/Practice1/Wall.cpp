// Fill out your copyright notice in the Description page of Project Settings.

#include "Wall.h"


// Sets default values
AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Wall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WALL"));
	
	RootComponent = Wall;
	Trigger->SetupAttachment(Wall);
	Wall->SetSimulatePhysics(true);

	Trigger->SetRelativeLocation(FVector(0.9f, 1.4f, 2.0f));
	Trigger->SetBoxExtent(FVector(3.0f, 3.0f, 1.8f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/OBJECT/WoodBox/Wood_Box.Wood_Box"));
	if (SM_BOX.Succeeded()) {
		Wall->SetStaticMesh(SM_BOX.Object);
	}
	Wall->SetRelativeScale3D(FVector(18.0f, 18.0f, 18.0f));
	Trigger->SetCollisionProfileName(TEXT("TreasureBox"));
	Wall->SetCollisionProfileName(TEXT("BlockAll"));
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWall::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AWall::EndCharacterOverlap);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWall::OnCharacterOverlap);
}

void AWall::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
//	OtherActor->castTo
}

void AWall::EndCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}
