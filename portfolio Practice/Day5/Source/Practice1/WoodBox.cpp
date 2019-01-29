// Fill out your copyright notice in the Description page of Project Settings.

#include "WoodBox.h"
#include "Practice1Character.h"

// Sets default values
AWoodBox::AWoodBox()
{
	PrimaryActorTick.bCanEverTick =false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	BoxRange = CreateDefaultSubobject<UBoxComponent>(TEXT("BOXRANGE"));
	BoxPhysicsConstraintX = CreateDefaultSubobject< UPhysicsConstraintComponent>(TEXT("BoxPhysicsConstraintX"));
	BoxPhysicsConstraintY = CreateDefaultSubobject< UPhysicsConstraintComponent>(TEXT("BoxPhysicsConstraintY"));

	RootComponent = Box;
	Trigger->SetupAttachment(Box);
	BoxPhysicsConstraintX->SetupAttachment(Box);
	BoxPhysicsConstraintY->SetupAttachment(Box);
	BoxRange->SetupAttachment(Box);

	BoxPhysicsConstraintX->ComponentName1.ComponentName = "Box";
	BoxPhysicsConstraintX->SetLinearXLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	BoxPhysicsConstraintX->SetLinearYLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	BoxPhysicsConstraintX->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	BoxPhysicsConstraintX->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 45.0f);
	BoxPhysicsConstraintX->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);
	BoxPhysicsConstraintX->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);

	BoxPhysicsConstraintY->ComponentName1.ComponentName = "Box";
	BoxPhysicsConstraintY->SetLinearXLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	BoxPhysicsConstraintY->SetLinearYLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	BoxPhysicsConstraintY->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	BoxPhysicsConstraintY->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 45.0f);
	BoxPhysicsConstraintY->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);
	BoxPhysicsConstraintY->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);
	BoxPhysicsConstraintY->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	Box->SetSimulatePhysics(true);
	Box->SetLinearDamping(5.0f);
	Box->SetAngularDamping(0.5f);
	Box->SetMassOverrideInKg("Box",350.0f);

	BoxRange->SetRelativeLocation(FVector(0.8f, 1.66f, 2.222f));
	BoxRange->SetRelativeScale3D(FVector(0.08f, 0.08f, 0.04f));

	Trigger->SetRelativeLocation(FVector(0.9f,1.4f, 2.0f));
	Trigger->SetBoxExtent(FVector(3.0f,3.0f,1.8f));

	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/OBJECT/WoodBox/Wood_Box.Wood_Box"));
	if (SM_BOX.Succeeded()) {
		Box->SetStaticMesh(SM_BOX.Object);
	}
	Box->SetRelativeScale3D(FVector(18.0f, 18.0f, 18.0f));
	Trigger->SetCollisionProfileName(TEXT("TreasureBox"));
	Box->SetCollisionProfileName(TEXT("BlockAll"));
	BoxRange->SetCollisionProfileName(TEXT("BlockAll"));
}

void AWoodBox::BeginPlay()
{
	Super::BeginPlay();

}

void AWoodBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AWoodBox::EndCharacterOverlap);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWoodBox::OnCharacterOverlap);
	//Trigger->OnComponentEndOverlap.AddDynamic(this, &AWoodBox::EndCharacterOverlap);
}

void AWoodBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto ABCharacter = Cast<APractice1Character>(OtherActor);
	ABCHECK(nullptr != ABCharacter);
	if (ABCharacter) {
		ABCharacter->MoveObject(true);
		ABLOG(Warning, TEXT("Push"));
	}
}

void AWoodBox::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto ABCharacter = Cast<APractice1Character>(OtherActor);
	ABCHECK(nullptr != ABCharacter);
	if (ABCharacter) {
		ABCharacter->MoveObject(false);
		ABLOG(Warning, TEXT("Out"));
	}
}
