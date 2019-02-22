// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "P2PlayerController.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyMesh"));
	EnemyState = CreateDefaultSubobject<UEnemyState>(TEXT("EnemyState"));
	pawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("pawnSensing"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> m_Skeletal2(TEXT("/Game/EnemyCharacter/Bokoblin/Bokobline.Bokobline"));
	if (m_Skeletal2.Succeeded()) {
		EnemyMesh->SetSkeletalMesh(m_Skeletal2.Object);
	}

	EnemyMesh->SetupAttachment(GetMesh());
	GetCapsuleComponent()->SetCapsuleRadius(30);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -50.0f), FRotator(0.0f, -90.0f, 0.0f));

	EnemyMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> Player_ANIM(TEXT("/Game/EnemyCharacter/AnimInstance/EnemyAnim.EnemyAnim_C"));
	if (Player_ANIM.Succeeded()) {
		EnemyMesh->SetAnimInstanceClass(Player_ANIM.Class);
	}

	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	MaxSpeed = 100.0f;

	pawnSensing->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnPawnSeen);
	pawnSensing->SetPeripheralVisionAngle(35.0f);
	findPlayer = false;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;

}

void AEnemyCharacter::OnPawnSeen(APawn * SeenPawn)
{
	findPlayer = false;
	if (SeenPawn != nullptr) {
		APlayerCharacter* PlayerCharacter = Cast< APlayerCharacter>(SeenPawn);
		if (PlayerCharacter != nullptr) {
			ABLOG(Warning, TEXT("FIND player"));
			return;
		}
		ABLOG(Warning, TEXT("FIND APawn"));
		return;
	}
	ABLOG(Warning, TEXT("Not Find"));
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

