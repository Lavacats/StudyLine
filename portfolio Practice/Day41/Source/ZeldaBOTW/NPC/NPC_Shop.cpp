// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_Shop.h"
#include "Player/Controller/PlayerCharacterController.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"

// Sets default values
ANPC_Shop::ANPC_Shop()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NPCMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NPCMesh"));
	DetectMark = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	DetectMark->SetupAttachment(GetMesh());
	DetectMark->SetWidgetSpace(EWidgetSpace::World);

	static ConstructorHelpers::FClassFinder<UUserWidget> m_UI(TEXT("/Game/UI/NPC_UI.NPC_UI_C"));
	if (m_UI.Succeeded()) {
		DetectMark->SetWidgetClass(m_UI.Class);
		DetectMark->SetDrawSize(FVector2D(100.f, 100.f));
	}
	DetectMark->SetRelativeLocation(FVector(-20.f, 0, 130.0f));
	static ConstructorHelpers::FClassFinder<UAnimInstance> NPC_ANIM(TEXT("/Game/Character/NPC/Animation/NPCANIMATION.NPCANIMATION_C"));
	if (NPC_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(NPC_ANIM.Class);
	}
	ShopRange = 100.0f;
}

// Called when the game starts or when spawned
void ANPC_Shop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC_Shop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PController = Cast< APlayerCharacterController>(PlayerController);
	float distanceToPlayer = FVector::Dist(GetActorLocation(), PController->getPlayerCharacter()->GetActorLocation());

	if (distanceToPlayer < ShopRange) {
		DetectMark->SetVisibility(true);
	}
	else {
		DetectMark->SetVisibility(false);
	}
	if (::IsValid(PlayerController)) {
		if (PController->getPlayerCharacter()) {
			FVector Xrotator = (DetectMark->GetComponentLocation() - PController->getPlayerCharacter()->getPlayerCamera()->GetComponentLocation());
			DetectMark->SetWorldRotation(FRotator(0, Xrotator.Rotation().Yaw,0) + FRotator(0, 180.0f, 0));
		}
	}
}

// Called to bind functionality to input
void ANPC_Shop::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

