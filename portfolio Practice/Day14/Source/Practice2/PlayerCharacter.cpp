// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "DrawDebugHelpers.h"

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
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//PlayerCamera->CameraVector();


}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

