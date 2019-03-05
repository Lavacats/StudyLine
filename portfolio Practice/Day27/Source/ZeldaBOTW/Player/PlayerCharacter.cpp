// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Weapon_Sword.h"
#include "Player/Controller/PlayerCharacterController.h"
#include "Player/PlayerWeapon.h"

void APlayerCharacter::getWeapon(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("Weapon")) {
		AWeapon_Sword* EquapWeapon2 = Cast<AWeapon_Sword>(OtherActor);
		if (EquapWeapon2 != nullptr) {
			ABLOG(Warning, TEXT("GetWaepon"));
			auto PlayerController = GetWorld()->GetFirstPlayerController();
			APlayerCharacterController* PController = Cast< APlayerCharacterController>(PlayerController);
			EquapWeapon2->getSwordMesh()->SetSimulatePhysics(false);
			PController->getPlayerWeapon()->AddSwordList(EquapWeapon2);
			EquapWeapon2->getSwordMesh()->SetVisibility(false);

		}
	}
}

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerMeshComponent = CreateDefaultSubobject<UPlayerMesh>(TEXT("PlayerMeshComponent"));
	PlayerCamera = CreateDefaultSubobject<UPlayerCamera>(TEXT("PlayerCamera"));


	PlayerMeshComponent->SetRootSkeletalMeshComponent(GetMesh());
	PlayerCamera->setSpringArmCameraInRoot(GetCapsuleComponent());

	GetCapsuleComponent()->SetCapsuleRadius(10);
	GetCapsuleComponent()->SetCapsuleHalfHeight(30);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -32.0f), FRotator(0.0f, -90.0f, 0.0f));
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->GravityScale = 1.0f;

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	PlayerMeshComponent->SetAnimClass(TEXT("/Game/PlayerCharacter/Animation/BP_Animation/PlayerBPAnimation.PlayerBPAnimation_C"));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = 20.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));
	GetCapsuleComponent()->ComponentTags.Add(FName("PlayerCharacter"));
}
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::getWeapon);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

