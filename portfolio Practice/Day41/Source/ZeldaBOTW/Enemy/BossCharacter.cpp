// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacter.h"
#include "Enemy/AI/BossAIController.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Player/Controller/PlayerCharacterController.h"
#include "Components/ProgressBar.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ABossCharacter::ABossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BossHeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BossMesh"));
	BossState = CreateDefaultSubobject<UEnemyCharacterState>(TEXT("BossState"));

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

	static ConstructorHelpers::FClassFinder<UBossUIClass> UI_AIM(TEXT("/Game/UI/BossUI.BossUI_C"));
	if (UI_AIM.Succeeded()) {
		HDWidgetClass = UI_AIM.Class;
	}
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	BossUI = CreateWidget<UBossUIClass>(Cast< APlayerCharacterController>(GetWorld()->GetFirstPlayerController()), HDWidgetClass);
	BossUI->AddToViewport();
	BossUI->SetVisibility(ESlateVisibility::Hidden);
	BossState->setMaxHP(100.f);
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

void ABossCharacter::setBossHPUI(bool value)
{
	if (value)
	{
		BossUI->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		BossUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ABossCharacter::HurtBoss()
{
	BossState->HurtEnemy();
	BossUI->SetHP(BossState->getCurHp(), BossState->getMaxHp());
	BossState->setCurEnemyState(EnemyState::Enemy_IDLE);
}

