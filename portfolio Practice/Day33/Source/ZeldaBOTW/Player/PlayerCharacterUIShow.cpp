// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacterUIShow.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget2D.h"

// Sets default values
APlayerCharacterUIShow::APlayerCharacterUIShow()
{
 	PrimaryActorTick.bCanEverTick = true;

	PlayerUICamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerUICamera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	playerCaputre = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("playerCaputre"));

	faceMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FaceMesh"));
	hairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	upperMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperMesh"));
	underMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UnderMesh"));

	SetSkeletalMeshComponent(faceMesh, TEXT("/Game/PlayerCharacter/Mesh/PlayerMesh/Face/PlayerCharacter.PlayerCharacter"));
	SetSkeletalMeshComponent(hairMesh, TEXT("/Game/PlayerCharacter/Mesh/PlayerMesh/Hair/1/Hair.Hair"));
	SetSkeletalMeshComponent(upperMesh, TEXT("/Game/PlayerCharacter/Mesh/PlayerMesh/Pants/1/Pants.Pants"));
	SetSkeletalMeshComponent(underMesh, TEXT("/Game/PlayerCharacter/Mesh/PlayerMesh/Shirts/1/shirts2.shirts2"));

	faceMesh->SetupAttachment(GetMesh());
	hairMesh->SetupAttachment(faceMesh);
	upperMesh->SetupAttachment(faceMesh);
	underMesh->SetupAttachment(faceMesh);

	GetCapsuleComponent()->SetCapsuleRadius(10);
	GetCapsuleComponent()->SetCapsuleHalfHeight(30);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 180.0f, 0.0f));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	PlayerUICamera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength =75.0f;
	SpringArm->SetRelativeRotation(FRotator(-10.0f, 90.0f, 0.0f));

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	SetAnimClass(TEXT("/Game/PlayerCharacter/Animation/BP_Animation/PlayerUI.PlayerUI_C"));

	playerCaputre->SetupAttachment(SpringArm);
	SetMeshPosition(0, 0, -42.0f);
	ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> m_Texture(TEXT("/Game/UI/PlayerUI/PlayerUI.PlayerUI"));
	if (m_Texture.Succeeded()) {
		playerCaputre->TextureTarget = m_Texture.Object;
	}
}

// Called when the game starts or when spawned
void APlayerCharacterUIShow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacterUIShow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacterUIShow::SetSkeletalMeshComponent(USkeletalMeshComponent * skeletalMesh, const TCHAR * Channel)
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> m_Skeletal(Channel);
	if (m_Skeletal.Succeeded()) {
		skeletalMesh->SetSkeletalMesh(m_Skeletal.Object);
	}
}


void APlayerCharacterUIShow::SetAnimClass(const TCHAR * AnimChannel)
{
	static ConstructorHelpers::FClassFinder<UAnimInstance> Player_ANIM(AnimChannel);
	if (Player_ANIM.Succeeded()) {
		faceMesh->SetAnimInstanceClass(Player_ANIM.Class);
		hairMesh->SetAnimInstanceClass(Player_ANIM.Class);
		upperMesh->SetAnimInstanceClass(Player_ANIM.Class);
		underMesh->SetAnimInstanceClass(Player_ANIM.Class);
	}
}

void APlayerCharacterUIShow::SetMeshPosition(float X, float Y, float Z)
{
	faceMesh->SetRelativeLocation(FVector(X, Y, Z));
}
