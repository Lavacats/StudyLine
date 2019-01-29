// Fill out your copyright notice in the Description page of Project Settings.

#include "Practice1Character.h"
#include "PracticeAnimInstance.h"
#include "DrawDebugHelpers.h"
// Sets default values
APractice1Character::APractice1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	hairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	upperMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperMesh"));
	underMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UnderMesh"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetCapsuleComponent()->SetCapsuleRadius(10);
	GetCapsuleComponent()->SetCapsuleHalfHeight(30);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -34.0f),FRotator(0.0f,-90.0f,0.0f));
	
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Root_Mesh(TEXT("/Game/PlayerCharacter/LINK_FBX/Idle.Idle"));
	if (Root_Mesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(Root_Mesh.Object);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> hairSkeletal(TEXT("/Game/PlayerCharacter/Hair/1/Hair.Hair"));
	if (hairSkeletal.Succeeded()) {
		hairMesh->SetSkeletalMesh(hairSkeletal.Object);
	}
	hairMesh->SetupAttachment(GetMesh());
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> shirtsSkeletal(TEXT("/Game/PlayerCharacter/Shirts/1/shirts2.shirts2"));
	if (shirtsSkeletal.Succeeded()) {
		upperMesh->SetSkeletalMesh(shirtsSkeletal.Object);
	}
	upperMesh->SetupAttachment(GetMesh());
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> pantsSkeletal(TEXT("/Game/PlayerCharacter/Pants/1/Pants.Pants"));
	if (pantsSkeletal.Succeeded()) {
		underMesh->SetSkeletalMesh(pantsSkeletal.Object);
	}
	underMesh->SetupAttachment(GetMesh());

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> Player_ANIM(TEXT("/Game/PlayerCharacter/BP_Animation/Animation_BP.Animation_BP_C"));
	if (Player_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(Player_ANIM.Class);
		hairMesh->SetAnimInstanceClass(Player_ANIM.Class);
		upperMesh->SetAnimInstanceClass(Player_ANIM.Class);
		underMesh->SetAnimInstanceClass(Player_ANIM.Class);
	}


	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->GravityScale = 1.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = -20.0f;

}


// Called when the game starts or when spawned
void APractice1Character::BeginPlay()
{
	Super::BeginPlay();
	EplayerState = E_PlayerState::Player_IDLE;
	auto body = Cast<UPracticeAnimInstance>(GetMesh()->GetAnimInstance());
	auto hair = Cast<UPracticeAnimInstance>(hairMesh->GetAnimInstance());
	auto upperBody = Cast<UPracticeAnimInstance>(upperMesh->GetAnimInstance());
	auto downBody = Cast<UPracticeAnimInstance>(underMesh->GetAnimInstance());
	body->SetMeshPartsOfPlayer((AnimationPats)0);
	hair->SetMeshPartsOfPlayer((AnimationPats)1);
	upperBody->SetMeshPartsOfPlayer((AnimationPats)2);
	downBody->SetMeshPartsOfPlayer((AnimationPats)3);
}

// Called every frame
void APractice1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnJumpCheck();
	//FHitResult* HitResult = new FHitResult();
	//FVector StartTrace = GetRootComponent()->GetComponentLocation();
	//FVector ForwardVector = this->GetActorForwardVector();
	//FVector EndTrace = (ForwardVector*500.0f) + StartTrace;
	//FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	//if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	//{
	//	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), true);
	//}
//#if ENABLE_DRAW_DEBUG
//	FVector TraceVec = GetActorForwardVector();
//	FVector Center = GetActorLocation() + TraceVec * 0.5f;
//
//	DrawDebugCapsule(
//		GetWorld(),
//		// 캡슐을 World에 생성하며
//		Center,
//		// Center를 중심으로
//		GetCapsuleComponent()->GetScaledCapsuleHalfHeight(),
//		GetCapsuleComponent()->GetScaledCapsuleRadius(),
//		FRotationMatrix::MakeFromX(TraceVec).ToQuat() ,
//		FColor::Green,
//		false,
//		5.0f
//	);
//#endif
}

// Called to bind functionality to input
void APractice1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"),  this, &APractice1Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &APractice1Character::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APractice1Character::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APractice1Character::Turn);


	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Pressed, this, &APractice1Character::RunToWalk);
	PlayerInputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Released, this, &APractice1Character::Stop);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &APractice1Character::WalkToRun);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &APractice1Character::RunToWalk);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &APractice1Character::PlayerCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &APractice1Character::PlayerUnCrouch);
}

void APractice1Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APractice1Character::OnCharacterOverlap);
	ABLOG(Warning, TEXT("Start"));
}

void APractice1Character::UpDown(float NewAxisValue)
{
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue*characterMoveSpeed);
}

void APractice1Character::LeftRight(float NewAxisValue)
{
	if (!GetMovementComponent()->IsFalling() )
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue*characterMoveSpeed);
}

void APractice1Character::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void APractice1Character::Turn(float NewAxisValue)
{
		AddControllerYawInput(NewAxisValue);
}

void APractice1Character::WalkToRun()
{
	PlayerMovement(E_PlayerState::Player_RUN);

}

void APractice1Character::RunToWalk()
{
	PlayerMovement(E_PlayerState::Player_WALK);
}

void APractice1Character::Stop()
{
	PlayerMovement(E_PlayerState::Player_IDLE);
}

void APractice1Character::PlayerMovement(E_PlayerState State)
{
	switch (State)
	{
	case E_PlayerState::Player_IDLE:

		characterMoveSpeed = 0.0f;
		if(EplayerState!= E_PlayerState::Player_COLLECT) EplayerState = E_PlayerState::Player_IDLE;
		break;
	case E_PlayerState::Player_WALK:
		characterMoveSpeed =0.5f;
		EplayerState = E_PlayerState::Player_WALK;
		break;
	case E_PlayerState::Player_RUN:
		if (EplayerState == E_PlayerState::Player_WALK) {
			EplayerState = E_PlayerState::Player_RUN;
			characterMoveSpeed = 1.0f;
		}
		break;
	}
}

void APractice1Character::OnJumpCheck()
{
	static E_PlayerState preState;
	if (GetMovementComponent()->IsFalling() && EplayerState != E_PlayerState::Player_JUMP) {
		preState = EplayerState;
		EplayerState = E_PlayerState::Player_JUMP;
		inPlayerOnAir = true;
	}
	if (GetMovementComponent()->IsMovingOnGround() && inPlayerOnAir) {
		inPlayerOnAir = false;
		EplayerState = preState;
	}
}

void APractice1Character::PlayerCrouch()
{

	Crouch();
	EplayerState = E_PlayerState::Player_CROUCH;
}

void APractice1Character::PlayerUnCrouch()
{

	UnCrouch();
	EplayerState = E_PlayerState::Player_IDLE;
}

void APractice1Character::SetCollectAnimation(int Collect)
{
	auto body = Cast<UPracticeAnimInstance>(GetMesh()->GetAnimInstance());
	auto hair = Cast<UPracticeAnimInstance>(hairMesh->GetAnimInstance());
	auto upperBody = Cast<UPracticeAnimInstance>(upperMesh->GetAnimInstance());
	auto downBody = Cast<UPracticeAnimInstance>(underMesh->GetAnimInstance());
	EplayerState = E_PlayerState::Player_COLLECT;
	body->SetCollectState((E_PlayerCollect)Collect);
	hair->SetCollectState((E_PlayerCollect)Collect);
	upperBody->SetCollectState((E_PlayerCollect)Collect);
	downBody->SetCollectState((E_PlayerCollect)Collect);
}

void APractice1Character::EndCollect()
{
	EplayerState = E_PlayerState::Player_IDLE;
}

void APractice1Character::MoveObject(bool value)
{
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = GetRootComponent()->GetComponentLocation();
	FVector ForwardVector = this->GetActorForwardVector();
	FVector EndTrace = (ForwardVector*500.0f) + StartTrace;
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	if (value) {
		if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
		{
			auto body = Cast<UPracticeAnimInstance>(GetMesh()->GetAnimInstance());
			auto hair = Cast<UPracticeAnimInstance>(hairMesh->GetAnimInstance());
			auto upperBody = Cast<UPracticeAnimInstance>(upperMesh->GetAnimInstance());
			auto downBody = Cast<UPracticeAnimInstance>(underMesh->GetAnimInstance());

			EplayerState = E_PlayerState::Player_PUSH;
			body->SerPushBool(value);
			hair->SerPushBool(value);
			upperBody->SerPushBool(value);
			downBody->SerPushBool(value);
		}
	}
	else {
		auto body = Cast<UPracticeAnimInstance>(GetMesh()->GetAnimInstance());
		auto hair = Cast<UPracticeAnimInstance>(hairMesh->GetAnimInstance());
		auto upperBody = Cast<UPracticeAnimInstance>(upperMesh->GetAnimInstance());
		auto downBody = Cast<UPracticeAnimInstance>(underMesh->GetAnimInstance());

		EplayerState = E_PlayerState::Player_IDLE;
		body->SerPushBool(value);
		hair->SerPushBool(value);
		upperBody->SerPushBool(value);
		downBody->SerPushBool(value);
	}

}

void APractice1Character::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABLOG(Warning, TEXT("Overlap"));
	if (OtherActor->ActorHasTag("Climing")) {
		ABLOG(Warning, TEXT("Climing"));
	}
}

