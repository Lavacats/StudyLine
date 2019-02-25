// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "Weapon_Sword.h"
#include "P2PlayerController.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyMesh"));
	EnemyState = CreateDefaultSubobject<UEnemyState>(TEXT("EnemyState"));
	pawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("pawnSensing"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	WeaponLocation = CreateDefaultSubobject<AWeapon_Sword>(TEXT("WeaponLocation"));
	PlayerCharacterPawn = CreateDefaultSubobject<ACharacter>(TEXT("PlayerCharacter"));
	EquapWeapon = CreateDefaultSubobject<AWeapon_Sword>(TEXT("EquapWeapon"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> m_Skeletal2(TEXT("/Game/EnemyCharacter/Bokoblin/Bokobline.Bokobline"));
	if (m_Skeletal2.Succeeded()) {
		EnemyMesh->SetSkeletalMesh(m_Skeletal2.Object);
	}

	EnemyMesh->SetupAttachment(GetMesh());
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 20.0f, 120.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::World);
	static ConstructorHelpers::FClassFinder<UUserWidget> m_UI(TEXT("/Game/UI/exclamation.exclamation_C"));
	if (m_UI.Succeeded()) {
		HPBarWidget->SetWidgetClass(m_UI.Class);
		HPBarWidget->SetDrawSize(FVector2D(12.0f, 35.0f));
	}

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
	OnBattle = false;
	hasWeapon = false;
	InAttackRange = false;
	AttackTimer = 10.0f;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::getWeapon);
	
	
}

void AEnemyCharacter::OnPawnSeen(APawn * SeenPawn)
{
	if (SeenPawn != nullptr) {
		APlayerCharacter* PlayerCharacter = Cast< APlayerCharacter>(SeenPawn);
		if (PlayerCharacter != nullptr) {
			OnBattle = true;
			PlayerCharacterPawn = SeenPawn;
			GetWorldTimerManager().ClearTimer(AttackTimerHandle);
			GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AEnemyCharacter::BattleToIdle, 1.0f, true, 0.0f);
			AttackTimer = 10.0f;
			return;
		}
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HPBarWidget->GetComponentLocation();
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (::IsValid(PlayerController)) {
		auto PController = Cast< AP2PlayerController>(PlayerController);
		if (PController->getPlayerCharacter()){
			FVector Xrotator = (HPBarWidget->GetComponentLocation() - PController->getPlayerCharacter()->getPlayerCamera()->GetComponentLocation());
			HPBarWidget->SetWorldRotation(Xrotator.Rotation()+FRotator(0,180.0f,0));
		}
	}
	if (OnBattle) {
		HPBarWidget->SetVisibility(true);

	}
	else {
		HPBarWidget->SetVisibility(false);
	}

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::BattleToIdle()
{
	if (AttackTimer-- <= 0)
	{
		GetWorldTimerManager().ClearTimer(AttackTimerHandle);
		OnBattle = false;
		PlayerCharacterPawn = NULL;
	}
}

void AEnemyCharacter::getWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Weapon") && !hasWeapon) {
		auto EquapWeapon2 = Cast<AWeapon_Sword>(OtherActor);
		EquapWeapon2->setCharacterEquip(EnemyMesh, TEXT("RightHandSocket"));
		hasWeapon = true;
	}
}

FVector AEnemyCharacter::getWeaponLocation()
{
	return WeaponLocation->GetActorLocation();
}

