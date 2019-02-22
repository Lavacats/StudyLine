// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Arrow.h"
#include "DrawDebugHelpers.h"

AWeapon_Arrow::AWeapon_Arrow()
{
 	PrimaryActorTick.bCanEverTick = true;
	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
	ArrowComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetCapsuleRadius(3);
	ArrowComponent->SetCapsuleHalfHeight(15);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_ARROW(TEXT("/Game/OBJECT/Bow/Arrow/WeaponArrow.WeaponArrow"));
	if (SK_ARROW.Succeeded()) {
		ArrowMesh->SetStaticMesh(SK_ARROW.Object);
	}
	RootComponent = ArrowComponent;
	ArrowMesh->SetupAttachment(ArrowComponent);
	ArrowMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ArrowMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	ArrowComponent->SetSimulatePhysics(true);
	ArrowComponent->SetEnableGravity(false);
	ArrowComponent->SetCollisionProfileName(TEXT("Weapon"));
	ArrowComponent->GetBodyInstance()->bLockXRotation = true;
	ArrowComponent->GetBodyInstance()->bLockYRotation = true;
	ArrowComponent->GetBodyInstance()->bLockZRotation = true;
	Velocity = FVector::ZeroVector;
	gravityBullte = 200.0f;
	ArrowComponent->ComponentTags.Add(FName("Weapon"));
	touchActor = false;
	CrushVec = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void AWeapon_Arrow::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeapon_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;

	FVector StartTrace;
	StartTrace = this->GetActorLocation();
	FVector EndTrace = (Velocity*DeltaTime) + StartTrace;
	
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult,StartTrace,EndTrace,ECC_Destructible,CollisionParams))
	{
		if (HitResult.GetActor())
		{
			Velocity = FVector::ZeroVector;
			DrawDebugSolidBox(GetWorld(), HitResult.ImpactPoint, FVector(3.0f), FColor::Blue, true);
			CrushVec = this->GetActorLocation();
			gravityBullte = 0.0f;
			EndTrace = this->GetActorLocation();
			touchActor = true;

			ADestructibleActor* ArrowMesh = Cast<ADestructibleActor>(HitResult.GetActor());
			if (IsValid(ArrowMesh)){
				ArrowMesh->GetDestructibleComponent()->ApplyRadiusDamage(10.f, HitResult.ImpactPoint, 32.f, 10.f, false);
			}
		}
	}
	else
	{
		if(!touchActor){
			BulletExpiry+=DeltaTime;
			DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green,true);
			SetActorLocation(EndTrace);
			Velocity += FVector(0.0f, 0.0f, -gravityBullte)*DeltaTime;
		}
	}
	if (touchActor)
	{
		SetActorLocation(CrushVec);
		ArrowComponent->GetBodyInstance()->bLockXTranslation = true;
		ArrowComponent->GetBodyInstance()->bLockYTranslation = true;
		ArrowComponent->GetBodyInstance()->bLockZTranslation = true;
		ArrowComponent->SetVisibility(false);
		ArrowMesh->SetVisibility(false);
	}
}

