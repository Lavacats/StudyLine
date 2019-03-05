// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Arrow.h"
#include "DrawDebugHelpers.h"
#include "Enemy/EnemyCharacter.h"
#include "Enemy/EnemyCharacterState.h"
#include "Player/PlayerCharacter.h"
#include "Player/Controller/PlayerCharacterController.h"
#include "Player/PlayerCharacterState.h"

// Sets default values
AWeapon_Arrow::AWeapon_Arrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SK_ARROW(TEXT("/Game/OBJECT/Bow/Arrow/WeaponArrow.WeaponArrow"));
	if (SK_ARROW.Succeeded()) {
		ArrowMesh->SetStaticMesh(SK_ARROW.Object);
	}
	RootComponent = ArrowMesh;
	ArrowMesh->GetBodyInstance()->bLockXRotation = true;
	ArrowMesh->GetBodyInstance()->bLockYRotation = true;
	ArrowMesh->GetBodyInstance()->bLockZRotation = true;
	ArrowMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ArrowMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	ArrowMesh->SetNotifyRigidBodyCollision(true);


	ArrowMesh->SetSimulatePhysics(true);
	ArrowMesh->SetEnableGravity(false);
	ArrowMesh->SetCollisionProfileName(TEXT("Weapon"));
	Velocity = FVector::ZeroVector;
	gravityBullte = 200.0f;
	CrushVec = FVector::ZeroVector;
	ArrowMesh->ComponentTags.Add(FName("Weapon"));
	touchActor = false;
}

// Called when the game starts or when spawned
void AWeapon_Arrow::BeginPlay()
{
	Super::BeginPlay();
	ArrowMesh->OnComponentHit.AddDynamic(this, &AWeapon_Arrow::hitComponent);
}

void AWeapon_Arrow::hitComponent(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ArrowMesh->SetSimulatePhysics(false);
	ArrowMesh->AttachToComponent(Hit.GetComponent(), FAttachmentTransformRules::KeepWorldTransform);
}

// Called every frame
void AWeapon_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector StartTrace;
	StartTrace = this->GetActorLocation();
	FVector EndTrace = (Velocity*DeltaTime) + StartTrace;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Destructible, CollisionParams)) {
		if (HitResult.GetActor()) {
			if (hitEnemy) {
				if (!HitResult.GetComponent()->ComponentHasTag("PlayerCharacter") && !HitResult.GetComponent()->ComponentHasTag("Weapon")) {
					touchActor = true;
					Velocity = FVector::ZeroVector;
					gravityBullte = 0.0f;
					EndTrace = this->GetActorLocation();
					CrushVec = this->GetActorLocation();
					DrawDebugSolidBox(GetWorld(), HitResult.ImpactPoint, FVector(3.0f), FColor::Blue, true);
					ADestructibleActor* ArrowMesh = Cast<ADestructibleActor>(HitResult.GetActor());
					if (IsValid(ArrowMesh)) {
						ArrowMesh->GetDestructibleComponent()->ApplyRadiusDamage(10.f, HitResult.ImpactPoint, 32.f, 10.f, false);
					}

					AEnemyCharacter* EnemyCharacter = Cast< AEnemyCharacter>(HitResult.GetActor());
					if (EnemyCharacter != nullptr) {
						EnemyCharacter->getEnemyState()->setOnBattle(true);
						EnemyCharacter->Hurt();
						RootComponent->SetVisibility(false);
					}
				}
			}
			else if (hitPlayer) {
				if (!HitResult.GetComponent()->ComponentHasTag("Enemy") && !HitResult.GetComponent()->ComponentHasTag("Weapon")) {
					touchActor = true;
					Velocity = FVector::ZeroVector;
					gravityBullte = 0.0f;
					EndTrace = this->GetActorLocation();
					CrushVec = this->GetActorLocation();
					DrawDebugSolidBox(GetWorld(), HitResult.ImpactPoint, FVector(3.0f), FColor::Blue, true);
					ADestructibleActor* ArrowMesh = Cast<ADestructibleActor>(HitResult.GetActor());
					if (IsValid(ArrowMesh)) {
						ArrowMesh->GetDestructibleComponent()->ApplyRadiusDamage(10.f, HitResult.ImpactPoint, 32.f, 10.f, false);
					}
					APlayerCharacter* PlayerChracter = Cast< APlayerCharacter>(HitResult.GetActor());
					if (PlayerChracter != nullptr) {
						auto PlayerController = GetWorld()->GetFirstPlayerController();
						APlayerCharacterController* playerController = Cast< APlayerCharacterController>(PlayerController);
						if (playerController != nullptr) {
							playerController->PlayerHurt();
							RootComponent->SetVisibility(false);
						}
					}
				}
			}
		}
	}
	if (!touchActor) {
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true);
		SetActorLocation(EndTrace);
		Velocity += FVector(0.0f, 0.0f, -gravityBullte)*DeltaTime;
	}
	if (touchActor) {
		SetActorLocation(CrushVec);
		ArrowMesh->GetBodyInstance()->bLockXTranslation = true;
		ArrowMesh->GetBodyInstance()->bLockYTranslation = true;
		ArrowMesh->GetBodyInstance()->bLockZTranslation = true;

		auto PlayerController = GetWorld()->GetFirstPlayerController();
		APlayerCharacterController* PController = Cast< APlayerCharacterController>(PlayerController);
		APlayerCharacter* playerCharacter = PController->getPlayerCharacter();
		float dist = FVector::Dist(GetActorLocation(), playerCharacter->GetActorLocation());
		if (dist < 150.0f) {
			this->Destroy();
		}
	}
}

