// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	// Pawn�� ����� ������Ʈ����� �����ϰ� �����Ϳ��� ���� ���ϰ� �з��մϴ�
	
	RootComponent = Capsule;
	// ��Ʈ ������Ʈ�� ĸ���� �Ӵϴ�.
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	// Mesh�� SpringArm�� Capsule�� �ڽ����� �ֽ��ϴ�
	Camera->SetupAttachment(SpringArm);
	// Camera�� SpringArm�� �ڽ����� �ֽ��ϴ�.

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	// ĸ���� ���̿� ������ �����մϴ�.
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	// Mesh�� �ʱ���ġ(FVector)�� ȸ����(FRotator)�� �����մϴ�
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	// ���������� ���̿� ȸ������ �����մϴ�.

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOAD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOAD.Succeeded()) {
		Mesh->SetSkeletalMesh(SK_CARDBOAD.Object);
		// ����� SkeletaMesh ��������� �ҷ�����, �ҷ����µ� �����ߴٸ�, Mesh�� �����մϴ�.
	}
	
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	// Mesh�� AnimationBlueprint(�������Ʈ�� ����ϴ� �ִϸ��̼� ����)�� �����մϴ�.
	static ConstructorHelpers::FClassFinder<UAnimInstance>WARRIOR_ANIM(TEXT("/Game/Book/Animation/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANIM.Succeeded()) {
		Mesh->SetAnimInstanceClass(WARRIOR_ANIM.Class);
		// ����� UAnimInstance ��������� �ҷ�����, �ҷ����µ� �����ߴٸ�, Mesh�� �����մϴ�.
	}

}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	//Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//Mesh�� �ִϸ��̼� ��带 �����մϴ�.
	//UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Book/Animation/WarriorRun.WarriorRun"));
	//UAnimationAsset�� AnimAsset�� ����� �ִϸ��̼��� ��θ� �Է��մϴ�.
	//if (AnimAsset != nullptr) {
	//	Mesh->PlayAnimation(AnimAsset, true);
	//  ���������� �ҷ��� ��� �ִϸ��̼��� ����մϴ�.
	//}
	
}

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPawn::PossessedBy(AController * NewController)
{
	ABLOG_S(Warning);
	Super::PossessedBy(NewController);
}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABPawn::LeftRight);
	//BindAxis : Pawn�� ���� ��ȣ�� ���� �� �ֵ��� �Լ��� �����մϴ�.

}

void AABPawn::UpDown(float NewAxisValue)
{
	ABLOG(Warning, TEXT("%f"), NewAxisValue);
	//NewAxisValue : -1~1�� ���� ������ UpDown �Է°��� �ݴϴ�.

	AddMovementInput(GetActorForwardVector(), NewAxisValue);
	//AddMovementInput : -1~1�� ���� �޾� ���� �����̰� �մϴ�. ForwardVector����
}

void AABPawn::LeftRight(float NewAxisValue)
{
	ABLOG(Warning, TEXT("%f"), NewAxisValue);
	//NewAxisValue : -1~1�� ���� ������ LeftRight �Է°��� �ݴϴ�.

	AddMovementInput(GetActorRightVector(), NewAxisValue);	
	//AddMovementInput : -1~1�� ���� �޾� ���� �����̰� �մϴ�. RightVector����
}

