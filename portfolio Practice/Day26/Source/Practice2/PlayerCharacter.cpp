// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Weapon_Sword.h" 
#include "P2PlayerController.h"
#include "PlayerWeapon.h"
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerMeshComponent = CreateDefaultSubobject<UPlayerMeshs>(TEXT("PlayerMeshComponent"));
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

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::getWeapon);
}
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	


}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::getWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherComp->ComponentHasTag("Weapon")) {
		AWeapon_Sword* EquapWeapon2 = Cast<AWeapon_Sword>(OtherActor);
		if (EquapWeapon2 != nullptr) {
			ABLOG(Warning, TEXT("GetWaepon"));
			auto PlayerController = GetWorld()->GetFirstPlayerController();
			AP2PlayerController* PController = Cast< AP2PlayerController>(PlayerController);
			EquapWeapon2->getSwordMesh()->SetSimulatePhysics(false);
			PController->getPlayerWeapon()->AddSwordList(EquapWeapon2);
			EquapWeapon2->getSwordMesh()->SetVisibility(false);

		}
	}
}
