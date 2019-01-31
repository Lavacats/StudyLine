// Fill out your copyright notice in the Description page of Project Settings.

#include "PracticeItemBox.h"
#include "Practice1Character.h"
#include "PracticeAniminstance.h"

// Sets default values
APracticeItemBox::APracticeItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(30.0f, 25.0f, 60.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/OBJECT/TreasureBox/Box.Box"));
	if (SM_BOX.Succeeded()) {
		Box->SetStaticMesh(SM_BOX.Object);
	}
	Box->SetRelativeLocation(FVector(0.0f,20.0f, 0.0f));

	Trigger->SetCollisionProfileName(TEXT("TreasureBox"));
	Box->SetCollisionProfileName(TEXT("BlockAll"));

}

// Called when the game starts or when spawned
void APracticeItemBox::BeginPlay()
{
	Super::BeginPlay();

}

void APracticeItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APracticeItemBox::OnCharacterOverlap);
}

void APracticeItemBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Box_Character = Cast<APractice1Character>(OtherActor);
	ABCHECK(Box_Character);
	/*auto PlayerAnim = Cast< UPracticeAnimInstance>(Box_Character->GetMesh()->GetAnimInstance());
	ABCHECK(PlayerAnim);*/
	Box_Character->SetCollectAnimation((int)E_PlayerCollect::Collect_BOX);
}

