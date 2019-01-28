// Fill out your copyright notice in the Description page of Project Settings.

#include "WoodBox.h"
#include "Practice1Character.h"

// Sets default values
AWoodBox::AWoodBox()
{
	PrimaryActorTick.bCanEverTick =false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	BoxPhysicsConstraintX = CreateDefaultSubobject< UPhysicsConstraintComponent>(TEXT("BoxPhysicsConstraintX"));
	BoxPhysicsConstraintY = CreateDefaultSubobject< UPhysicsConstraintComponent>(TEXT("BoxPhysicsConstraintY"));
	BoxN = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxN"));
	BoxE = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxE"));
	BoxS = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxS"));
	BoxW = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxW"));

	RootComponent = Box;
	Trigger->SetupAttachment(Box);
	BoxPhysicsConstraintX->SetupAttachment(Box);
	BoxPhysicsConstraintY->SetupAttachment(Box);
	BoxN->SetupAttachment(Box);
	BoxE->SetupAttachment(Box);
	BoxS->SetupAttachment(Box);
	BoxW->SetupAttachment(Box);

	BoxPhysicsConstraintX->ComponentName1.ComponentName="Box";
	BoxPhysicsConstraintX->SetLinearXLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	BoxPhysicsConstraintX->SetLinearYLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	BoxPhysicsConstraintX->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.0f);
	BoxPhysicsConstraintX->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, 45.0f);
	BoxPhysicsConstraintX->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);
	BoxPhysicsConstraintX->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 45.0f);

	BoxPhysicsConstraintY->ComponentName1.ComponentName = "None";
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

	Trigger->SetRelativeLocation(FVector(0.9f,1.4f, 2.0f));
	Trigger->SetBoxExtent(FVector(2.5f,2.5f,1.8f));

	BoxN->SetRelativeLocation(FVector(2.77f, 1.66f, 2.22f));
	BoxN->SetBoxExtent(FVector(0.02f, 0.035f, 0.02f));
	BoxN->SetRelativeScale3D(FVector(40.0f, 40.0f, 40.0f));

	BoxE->SetRelativeLocation(FVector(0.55f,3.88f, 2.22f));
	BoxE->SetBoxExtent(FVector(0.02f, 0.035f, 0.02f));
	BoxE->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	BoxE->SetRelativeScale3D(FVector(40.0f, 40.0f, 40.0f));

	BoxS ->SetRelativeLocation(FVector(-1.66, 1.66f, 2.22f));
	BoxS->SetBoxExtent(FVector(0.02f, 0.035f, 0.02f));
	BoxS->SetRelativeScale3D(FVector(40.0f, 40.0f, 40.0f));

	BoxW->SetRelativeLocation(FVector(0.55f, -0.555f, 2.22f));
	BoxW->SetBoxExtent(FVector(0.02f, 0.035f, 0.02f));
	BoxW->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	BoxW->SetRelativeScale3D(FVector(40.0f, 40.0f, 40.0f));



	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/OBJECT/WoodBox/Wood_Box.Wood_Box"));
	if (SM_BOX.Succeeded()) {
		Box->SetStaticMesh(SM_BOX.Object);
	}
	//Box->SetRelativeLocation(FVector(-15.0f, -30.0f, -40.0f));
	Box->SetRelativeScale3D(FVector(18.0f, 18.0f, 18.0f));
	Trigger->SetCollisionProfileName(TEXT("TreasureBox"));
	BoxN->SetCollisionProfileName(TEXT("TreasureBox"));
	BoxE->SetCollisionProfileName(TEXT("TreasureBox"));
	BoxS->SetCollisionProfileName(TEXT("TreasureBox"));
	BoxW->SetCollisionProfileName(TEXT("TreasureBox"));
	Box->SetCollisionProfileName(TEXT("BlockAll"));
}

// Called when the game starts or when spawned
void AWoodBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWoodBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWoodBox::OnCharacterOverlap);
	//BoxN->OnComponentBeginOverlap.AddDynamic(this, &AWoodBox::OnCharacterImpactNorth);
	//BoxE->OnComponentBeginOverlap.AddDynamic(this, &AWoodBox::OnCharacterImpactEast);
	//BoxS->OnComponentBeginOverlap.AddDynamic(this, &AWoodBox::OnCharacterImpactSouth);
	//BoxW->OnComponentBeginOverlap.AddDynamic(this, &AWoodBox::OnCharacterImpactWest);

}

void AWoodBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto ABCharacter = Cast<APractice1Character>(OtherActor);
	ABCHECK(nullptr != ABCharacter);
	if (ABCharacter) {
	}
}

void AWoodBox::OnCharacterImpactNorth(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	BoxPhysicsConstraintX->ComponentName1.ComponentName = "NULL";
	BoxPhysicsConstraintY->ComponentName1.ComponentName = "None";
	ABLOG(Warning, TEXT("North"));
}

void AWoodBox::OnCharacterImpactEast(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	BoxPhysicsConstraintX->ComponentName1.ComponentName = "None";
	BoxPhysicsConstraintY->ComponentName1.ComponentName = "NULL";
	ABLOG(Warning, TEXT("East"));
}

void AWoodBox::OnCharacterImpactSouth(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	BoxPhysicsConstraintX->ComponentName1.ComponentName = "NULL";
	BoxPhysicsConstraintY->ComponentName1.ComponentName = "None";
	ABLOG(Warning, TEXT("South"));
}

void AWoodBox::OnCharacterImpactWest(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//BoxPhysicsConstraintX->ComponentName1.ComponentName = "None";
	//BoxPhysicsConstraintY->ComponentName1.ComponentName = "NULL";
	//ABLOG(Warning, TEXT("West"));
}

