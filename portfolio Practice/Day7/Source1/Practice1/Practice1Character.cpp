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
	SphereTracer = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTracer"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	SphereTracer->SetupAttachment(GetMesh());
	GetCapsuleComponent()->SetCapsuleRadius(10);
	GetCapsuleComponent()->SetCapsuleHalfHeight(30);

	SphereTracer->SetSphereRadius(40.0f);
	SphereTracer->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));

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

	SphereTracer->SetCollisionProfileName(TEXT("ladderCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = -20.0f;
	
	IsClimbingLedge = false;
	IsOnCliming = false;
	IsClimbingEnd = false;
	HeightLocation = FVector(0.0f, 0.0f, 0.0f);
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
	if (IsClimbingLedge) {
		PlayerForwardTraceCheck();
		PlayerHeightTraceCheck();
	}

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
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APractice1Character::EndCharacterOverlap);

}

void APractice1Character::UpDown(float NewAxisValue)
{
	if (GetCharacterMovement()->IsFlying()) {
		//FRotator FlyRotator = FRotator(GetControlRotation().Pitch, GetActorRotation().Yaw, GetActorRotation().Roll);
		//AddMovementInput(FRotationMatrix(FlyRotator).GetUnitAxis(EAxis::Z), NewAxisValue*characterMoveSpeed*0.1f);
		//AddActorLocalOffset(GetActorRightVector()*characterMoveSpeed);
		AddActorLocalOffset(GetActorUpVector()*characterMoveSpeed*NewAxisValue*2.0f);
	}
	else if (GetCharacterMovement()->IsMovingOnGround()) {
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue*characterMoveSpeed);
	}
}

void APractice1Character::LeftRight(float NewAxisValue)
{
	ABLOG(Warning, TEXT("X:%f, Y:%f, Z:%f"), GetActorRightVector().X, GetActorRightVector().Y, GetActorRightVector().Z);
	if (GetCharacterMovement()->IsFlying()) {
		SetActorLocation(GetActorLocation() + GetActorRightVector()*characterMoveSpeed*NewAxisValue*3.0f);
		//AddActorLocalOffset(GetActorRightVector()*characterMoveSpeed*NewAxisValue*3.0f);
	}
	else if (GetCharacterMovement()->IsMovingOnGround()) {
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue*characterMoveSpeed);
	}
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
	if (EplayerState != E_PlayerState::Player_CLIMING)
	{
		switch (State)
		{
		case E_PlayerState::Player_IDLE:

			characterMoveSpeed = 0.0f;
			if (EplayerState != E_PlayerState::Player_COLLECT) EplayerState = E_PlayerState::Player_IDLE;
			break;
		case E_PlayerState::Player_WALK:
			characterMoveSpeed = 0.5f;
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
	if (GetMovementComponent()->IsMovingOnGround()) {

		IsClimbingLedge = true;
	}
}

void APractice1Character::PlayerCrouch()
{
	if (GetMovementComponent()->IsFlying()) {
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		GetCharacterMovement()->AddForce(-GetActorForwardVector()*30.0f);
		EplayerState = E_PlayerState::Player_JUMP;
		IsClimbingLedge = false;
	}
	else
	{
		Crouch();
		EplayerState = E_PlayerState::Player_CROUCH;
	}
}

void APractice1Character::PlayerUnCrouch()
{

	UnCrouch();
	EplayerState = E_PlayerState::Player_IDLE;
}

void APractice1Character::PlayerForwardTraceCheck()
{
	FHitResult HitResult;
	float TraceRange = 20.0f;
	float TraceRadius = 5.0f;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult =
		GetWorld()->SweepSingleByChannel
		(
			HitResult,
			GetActorLocation(),
			GetActorLocation() + GetActorForwardVector()*TraceRange,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel2,
			FCollisionShape::MakeSphere(TraceRadius),
			Params
		);
	#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector()* TraceRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = TraceRange * 0.5f ;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	// 색상 초록 or 빨강
	float DebugLifeTime = 0.5f;
	// 디버그 라인 생성 시간 5초

	DrawDebugCapsule(
		GetWorld(),
		Center,
		HalfHeight,
		TraceRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime
	);
	#endif
    static bool touch = false;
	FVector wallNormal = HitResult.Normal;
	FVector wallLocation = HitResult.Location;
	
	if (bResult) {
		if (HitResult.GetActor()->ActorHasTag("Climing")) {

			if (!touch) {
				FRotator playerRo = wallNormal.Rotation();
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
				SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, playerRo.Yaw - 180.0f, GetActorRotation().Roll));
				SetActorRelativeLocation(FVector(wallNormal.X*TraceRange*0.5f + wallLocation.X, wallNormal.Y*TraceRange*0.5f + wallLocation.Y, wallLocation.Z));
				GetCharacterMovement()->StopMovementImmediately();
				touch = true;
			}
		}
	}
	else {
		touch = false;
	}
}

void APractice1Character::PlayerHeightTraceCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	float TraceRange = 45.0f;
	FVector TraceStart =FVector(0.0f,0.0f,60.0f);
	float TraceHeigth = 18.0f;
	float TraceRadius = 5.0f;
	bool bResult =
		GetWorld()->SweepSingleByChannel
		(
			HitResult,
			GetActorLocation() + GetActorForwardVector() * TraceRange+ TraceStart,
			GetActorLocation() + GetActorForwardVector() * TraceRange + TraceStart+FVector(0, 0, TraceHeigth),
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel2,
			FCollisionShape::MakeSphere(TraceRadius),
			Params
		);
	static bool check = false;

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorUpVector() * TraceRange;
	FVector Center = GetActorLocation() + GetActorForwardVector() * TraceRange + TraceVec * 0.5+ TraceStart;
	float HalfHeight = TraceHeigth * 0.5f;
	FQuat CapsuleRot = FRotationMatrix::Identity.ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 0.5f;

	DrawDebugCapsule(
		GetWorld(),
		Center,
		HalfHeight,
		TraceRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime
	);
#endif
	if (GetCharacterMovement()->IsFlying() && !bResult&& !check) 
	{
		auto body = Cast<UPracticeAnimInstance>(GetMesh()->GetAnimInstance());
		auto hair = Cast<UPracticeAnimInstance>(hairMesh->GetAnimInstance());
		auto upperBody = Cast<UPracticeAnimInstance>(upperMesh->GetAnimInstance());
		auto downBody = Cast<UPracticeAnimInstance>(underMesh->GetAnimInstance());
		body->SetClimingEnd(true);
		hair->SetClimingEnd(true);
		downBody->SetClimingEnd(true);
		upperBody->SetClimingEnd(true);
		
			check = true;
			GetCharacterMovement()->StopMovementImmediately();

		
		
	}
	else if(!GetCharacterMovement()->IsFlying()){
		check = false;
	}
	
}

void APractice1Character::GrabLedge()
{
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
	//ABLOG(Warning, TEXT("Overlap"));
	//if (OtherActor->ActorHasTag("Climing")) {
	//	ABLOG(Warning, TEXT("Climing"));
	//	if (!GetMovementComponent()->IsMovingOnGround()) {
	//		EplayerState = E_PlayerState::Player_CLIMING;
	//		//IsNearLadder = true;
	//		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	//		canTrace = true;
	//	}
	//}
}

void APractice1Character::EndCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	/*if (GetCharacterMovement()->IsFlying()) {
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		EplayerState = E_PlayerState::Player_IDLE;
	}*/
}

