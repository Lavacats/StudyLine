// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacter.h"
#include "Enemy/AI/BossAIController.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"

// Sets default values
ABossCharacter::ABossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BossMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BossMesh"));

	BossMesh->SetupAttachment(GetMesh());

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> Boss_Anim(TEXT("/Game/EnemyCharacter/GuardianBoss/anim/BossAnim.BossAnim_C"));
	if (Boss_Anim.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(Boss_Anim.Class);
	}
	patrolRange=1000.0f;
	FIndRange=100.0f;
	AttackRange=100.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	AIControllerClass = ABossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
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
	
	float pitch = 0.0f;
	float Yaw = 0.0f;
	float Roll = 0.0f;
	pitch = GetMesh()->GetSocketRotation("HeadGear").Pitch;
	Yaw = GetMesh()->GetSocketRotation("HeadGear").Pitch;
	Roll = GetMesh()->GetSocketRotation("HeadGear").Roll;
	ABLOG(Warning, TEXT("x:%f,y:%f,z:%f"), pitch, Yaw, Roll);

	int index = GetMesh()->GetBoneIndex("HeadGear");
	GetMesh()->GetBoneTransform(index).SetRotation(FQuat(0,0,0,0));

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

