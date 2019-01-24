// Fill out your copyright notice in the Description page of Project Settings.

#include "PracticeItemBox.h"


// Sets default values
APracticeItemBox::APracticeItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(30.0f, 25.0f, 30.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/OBJECT/TreasureBox/Box.Box"));
	if (SM_BOX.Succeeded()) {
		Box->SetStaticMesh(SM_BOX.Object);
	}
	Box->SetRelativeLocation(FVector(0.0f,20.0f, 0.0f));
}

// Called when the game starts or when spawned
void APracticeItemBox::BeginPlay()
{
	Super::BeginPlay();

}

