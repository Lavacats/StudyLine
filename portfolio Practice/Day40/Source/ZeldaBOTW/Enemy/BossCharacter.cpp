// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacter.h"
#include "Enemy/AI/BossAIController.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"

// Sets default values
ABossCharacter::ABossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BossHeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BossMesh"));

	BossHeadMesh->SetupAttachment(GetMesh());

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> Boss_Anim(TEXT("/Game/EnemyCharacter/GuardianBoss/anim/BossAnim.BossAnim_C"));
	if (Boss_Anim.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(Boss_Anim.Class);
	}
	patrolRange=1000.0f;
	FIndRange=100.0f;
	AttackRange=1000.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	AIControllerClass = ABossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	OnBattle = false;
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!OnBattle) {
		FRotator headRotator = FMath::RInterpTo(BossHeadMesh->RelativeRotation, GetMesh()->GetSocketRotation("HeadGear"), DeltaTime, 3.f);
		BossHeadMesh->SetRelativeRotation(headRotator);
	}


}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ABossCharacter::getTreasureLotation()
{
	return Treasure->GetActorLocation();
}

float ABossCharacter::getPatrolRange()
{
	return patrolRange;
}

float ABossCharacter::getFIndRange()
{
	return FIndRange;
}

float ABossCharacter::getAttackRange()
{
	return AttackRange;
}

