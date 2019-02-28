// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon_Arrow.h"
#include "DrawDebugHelpers.h"
#include "EnemyCharacter.h"
#include "EnemyState.h"
#include "PlayerCharacter.h"
#include "P2PlayerController.h"
#include "P2PlayerState.h"

AWeapon_Arrow::AWeapon_Arrow()
{
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
	//ArrowComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeapon_Arrow::ComponentHit);
	ArrowMesh->OnComponentHit.AddDynamic(this, &AWeapon_Arrow::hitComponent);
}

void AWeapon_Arrow::hitComponent(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	static bool hit = false;
	if (!hit) {
		if (!IsValid(OtherActor))return;
		UStaticMeshComponent* HitstaticMesh = Cast< UStaticMeshComponent>(Hit.GetActor());
		if (IsValid(HitstaticMesh)) {
			ArrowMesh->AttachToComponent(HitstaticMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			//OtherActor->Getstatic
		}
		hit = true;
	}
	//if (OtherComp->ComponentHasTag("PlayerCharacter")) {
		//ABLOG(Warning, TEXT("palyer"));
	//}
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

	if (GetWorld()->LineTraceSingleByChannel(HitResult,StartTrace,EndTrace,ECC_Destructible,CollisionParams)){
		if (HitResult.GetActor()){
			//if(HitResult.GetComponent())ArrowMesh->SetupAttachment(HitResult.GetComponent());
			if (hitEnemy) {
				if (!HitResult.GetComponent()->ComponentHasTag("PlayerCharacter")&& !HitResult.GetComponent()->ComponentHasTag("Weapon")){
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
			else if(hitPlayer) {
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
						AP2PlayerController* playerController = Cast< AP2PlayerController>(PlayerController);
						if (playerController != nullptr) {
							playerController->PlayerHurt();
							RootComponent->SetVisibility(false);
						}
					}
				}
			}
			//ABCHECK(HitResult.GetComponent());
			//
		}
	}
	if(!touchActor){
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green,true);
		SetActorLocation(EndTrace);
		Velocity += FVector(0.0f, 0.0f, -gravityBullte)*DeltaTime;
	}
	if (touchActor){
		SetActorLocation(CrushVec);
		ArrowMesh->GetBodyInstance()->bLockXTranslation = true;
		ArrowMesh->GetBodyInstance()->bLockYTranslation = true;
		ArrowMesh->GetBodyInstance()->bLockZTranslation = true;

		auto PlayerController = GetWorld()->GetFirstPlayerController();
		AP2PlayerController* PController = Cast< AP2PlayerController>(PlayerController);
		APlayerCharacter* playerCharacter = PController->getPlayerCharacter();
		float dist = FVector::Dist(GetActorLocation(), playerCharacter->GetActorLocation());
		if (dist < 150.0f) {
			this->Destroy();
		}
	}
}

