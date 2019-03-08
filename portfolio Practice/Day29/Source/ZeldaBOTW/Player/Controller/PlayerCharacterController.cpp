// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacterController.h"
#include "Player/PlayerCamera.h"
#include "DrawDebugHelpers.h"

APlayerCharacterController::APlayerCharacterController()
{
	PlayerTrace = CreateDefaultSubobject<UPlayerTrace>(TEXT("PlayerTrace"));
	p2PlayerSate = CreateDefaultSubobject<UPlayerCharacterState>(TEXT("p2PlayerSate"));
	PlayerWeapon = CreateDefaultSubobject<APlayerWeapon>(TEXT("PlayerWeapon"));
	CurArrrow = CreateDefaultSubobject<AWeapon_Arrow>(TEXT("CurArrrow"));
	IsJump = false;
	IsMove = false;
	IsBattle = true;
	IsClimming = false;
	IsShoot = false;
	CanShootArrow = false;
	IsSword = false;
	playerSpeed = 0.5f;
	playerCurSpeed = playerSpeed;
	WeaponIdleTime = 5;
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	PlayerWeapon = GetWorld()->SpawnActor<APlayerWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("PlayerBackStorage"));
	PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_ARROW_BAG, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("BackWaistSocket"));

}

void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	KeyDownCheck();
	PlayerJumpCheck();
	PlayerTrace->PlayerTraceCheck(p2PlayerCharacter->GetActorLocation(), p2PlayerCharacter->GetActorForwardVector(), p2PlayerCharacter);
	PlayerTracePushCheck();
	PlayerTraceClimmingCheck();
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("MoveForwardBack"), this, &APlayerCharacterController::ForwardBack);
	InputComponent->BindAxis(TEXT("MoveLeftRight"), this, &APlayerCharacterController::LeftRight);
	InputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacterController::Turn);
	InputComponent->BindAxis(TEXT("LookUpDown"), this, &APlayerCharacterController::LookUpDown);

	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::PlayerJump);
	InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::PlayerRunStart);
	InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &APlayerCharacterController::PlayerRunStop);
	InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::PlayerCrouch);
	InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &APlayerCharacterController::PlayerUnCrouch);

	InputComponent->BindAction(TEXT("Shot"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::PlayerShotStart);
	InputComponent->BindAction(TEXT("Shot"), EInputEvent::IE_Released, this, &APlayerCharacterController::PlayerShotEnd);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::PlayerAttackStart);

	InputComponent->BindAction(TEXT("WeaponChange1"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::WeaponChangeIDLE);
	InputComponent->BindAction(TEXT("WeaponChange2"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::WeaponChangeSword);
	InputComponent->BindAction(TEXT("WeaponChange3"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::WeaponChangeBow);
	InputComponent->BindAction(TEXT("Press4"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::PlayerHurt);

	InputComponent->BindAction(TEXT("ExtraInput"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::PlayerExtraState);

	InputComponent->BindAction(TEXT("WeaponChangeLeft"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::PlayerWeaponChangeLeft);
	InputComponent->BindAction(TEXT("WeaponChangeRight"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::PlayerWeaponChangeRight);

}

void APlayerCharacterController::Possess(APawn * aPawn)
{
	Super::Possess(aPawn);
	if (aPawn) {
		p2PlayerCharacter = Cast< APlayerCharacter>(aPawn);
	
	}
}

void APlayerCharacterController::KeyDownCheck()
{
	if (!IsInputKeyDown(EKeys::W) && !IsInputKeyDown(EKeys::S) && !IsInputKeyDown(EKeys::A) && !IsInputKeyDown(EKeys::D)) {
		if (p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
			if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {
				p2PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
			}
		}
		IsMove = false;
	}
	playerCurSpeed = playerSpeed;
}

void APlayerCharacterController::PlayerJumpCheck()
{
	if (IsJump)
	{
		if (p2PlayerCharacter->GetMovementComponent()->IsFalling() && !p2PlayerSate->CheckCurState(E_PlayerState::Player_JUMP)) {
			p2PlayerSate->setPlayerState(E_PlayerState::Player_JUMP);
		}
		else if (p2PlayerCharacter->GetMovementComponent()->IsMovingOnGround() && p2PlayerSate->CheckCurState(E_PlayerState::Player_JUMP)) {
			p2PlayerSate->setPlayerState(p2PlayerSate->getPrePlayerState());
			IsJump = false;
		}
	}
}

void APlayerCharacterController::ForwardBack(float NewAxisValue)
{
	if (p2PlayerCharacter->GetMovementComponent()->IsMovingOnGround()) {
		{
			p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
		}
	}
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING)) {
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorUpVector()*playerCurSpeed*NewAxisValue*0.5f);
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {
		if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SHIELD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
			p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue * playerCurSpeed);
		}

	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
		//p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue * playerCurSpeed*0.3f);
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorForwardVector()*playerCurSpeed*NewAxisValue*0.5f);
	}
	IsMove = true;
}

void APlayerCharacterController::LeftRight(float NewAxisValue)
{
	if (p2PlayerCharacter->GetMovementComponent()->IsMovingOnGround()) {
		p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
	}
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING)) {
		if (IsMove)p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorRightVector()*playerCurSpeed*NewAxisValue);
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {
		if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SHIELD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
			p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue * playerCurSpeed);
		}

	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorRightVector()*playerCurSpeed*NewAxisValue*0.5f);
	}
}

void APlayerCharacterController::LookUpDown(float NewAxisValue)
{
	float LookPitch = GetControlRotation().Pitch;
	float PitchMin = 330.0f;
	float PitchMax = 5.0f;
	if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT))
	{
		if (LookPitch > PitchMin || LookPitch < PitchMax) {
			LookPitch += NewAxisValue;
			if (LookPitch > PitchMin || LookPitch < PitchMax) {
				SetControlRotation(FRotator(LookPitch, GetControlRotation().Yaw, GetControlRotation().Roll));
			}
		}
		else if (LookPitch <= PitchMin) {
			LookPitch = PitchMin + NewAxisValue;
			SetControlRotation(FRotator(LookPitch, GetControlRotation().Yaw, GetControlRotation().Roll));
		}
		else if (LookPitch >= PitchMax) {
			LookPitch = PitchMax - NewAxisValue;
			SetControlRotation(FRotator(LookPitch, GetControlRotation().Yaw, GetControlRotation().Roll));
		}
	}
	else {
		p2PlayerCharacter->AddControllerPitchInput(-NewAxisValue);
	}
}

void APlayerCharacterController::Turn(float NewAxisValue)
{
	static bool shotCheck = false;
	static float rotationValue = 0.0f;
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT) && (p2PlayerCharacter->getPlayerCamera()->getPlayerViewState() == PlayerViewState::View_SHOT)) {

		static float LookYaw = 0.0f;

		if (!shotCheck) {
			rotationValue = GetControlRotation().Yaw;
			p2PlayerCharacter->SetActorRotation(FRotator(p2PlayerCharacter->GetActorRotation().Pitch, GetControlRotation().Yaw, p2PlayerCharacter->GetActorRotation().Roll));

			LookYaw = GetControlRotation().Yaw;
			shotCheck = true;
		}

		PlayerWeapon->ShowArrowLocationRotation(p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh()->GetSocketLocation(TEXT("LeftHandSocket")), GetControlRotation(), CanShootArrow);

		float YawMin = rotationValue - 45.0f;
		float YawMax = rotationValue + 45.0f;
		if (LookYaw >= YawMin && LookYaw <= YawMax) {
			LookYaw += NewAxisValue;
			if (LookYaw >= YawMin && LookYaw <= YawMax) {
				SetControlRotation(FRotator(GetControlRotation().Pitch, LookYaw, GetControlRotation().Roll));
			}
		}
		else if (LookYaw <= YawMin) {
			LookYaw = YawMin + NewAxisValue;
			SetControlRotation(FRotator(GetControlRotation().Pitch, LookYaw, GetControlRotation().Roll));
		}
		else if (LookYaw >= YawMax) {
			LookYaw = YawMax - NewAxisValue;
			SetControlRotation(FRotator(GetControlRotation().Pitch, LookYaw, GetControlRotation().Roll));
		}
	}
	else {
		shotCheck = false;
		p2PlayerCharacter->AddControllerYawInput(NewAxisValue);
	}
}

void APlayerCharacterController::PlayerJump()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE) || p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
		p2PlayerCharacter->Jump();
		IsJump = true;
	}
}

void APlayerCharacterController::PlayerRunStart()
{
	p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_WALK, E_PlayerState::Player_RUN);
	playerCurSpeed = playerSpeed * 1.5f;
}

void APlayerCharacterController::PlayerRunStop()
{
	p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_RUN, E_PlayerState::Player_WALK);
	playerCurSpeed = playerSpeed;
}

void APlayerCharacterController::PlayerCrouch()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE) ||
		p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) ||
		p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN))
	{
		p2PlayerSate->setPlayerState(E_PlayerState::Player_CROUCH);
		p2PlayerCharacter->Crouch();
	}
}

void APlayerCharacterController::PlayerUnCrouch()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CROUCH)) {
		p2PlayerCharacter->UnCrouch();
		p2PlayerSate->setPlayerState(p2PlayerSate->getPrePlayerState());
	}
}

void APlayerCharacterController::PlayerTracePushCheck()
{
	static bool PlayerPush = false;
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_PUSH) || p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
		if (PlayerTrace->getTracePush() && PlayerTrace->getTraceClose() && PlayerTrace->getTraceForward() && !PlayerPush) {
			p2PlayerSate->setPlayerState(E_PlayerState::Player_PUSH);
			p2PlayerCharacter->GetMesh()->SetRelativeLocation(FVector(-15.0f, 0, -32.0f));
			PlayerPush = true;
		}
		else if (!PlayerTrace->getTracePush() && !PlayerTrace->getTraceClose() && !PlayerTrace->getTraceForward() && PlayerPush) {
			p2PlayerSate->setPlayerState(p2PlayerSate->getPrePlayerState());
			p2PlayerCharacter->GetMesh()->SetRelativeLocation(FVector(0, 0, -32.0f));
			PlayerPush = false;
		}
	}
}

void APlayerCharacterController::PlayerTraceClimmingCheck()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING) || p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN) || p2PlayerSate->CheckCurState(E_PlayerState::Player_JUMP)) {
		if (PlayerTrace->getTraceHeight() && PlayerTrace->getTraceClimming() && PlayerTrace->getTraceClose() && PlayerTrace->getTraceForward() && !IsClimming) {
			p2PlayerSate->setPlayerState(E_PlayerState::Player_CLIMING);
			p2PlayerCharacter->GetCharacterMovement()->StopMovementImmediately();
			p2PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			IsClimming = true;
		}
		else if (!PlayerTrace->getTraceHeight() && PlayerTrace->getTraceClimming() && PlayerTrace->getTraceClose() && PlayerTrace->getTraceForward() && IsClimming) {
			IsClimming = false;

		}
		if (!PlayerTrace->getTraceClose() || !PlayerTrace->getTraceForward()) {
			if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING)) {
				p2PlayerSate->setPlayerState(p2PlayerSate->getPrePlayerState());
				p2PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
				IsClimming = false;
				playerCurSpeed = playerSpeed;
				p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorForwardVector()*2.0f);
			}
		}
	}
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING) && !IsClimming) {
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorUpVector()*0.75f);
	}
}

void APlayerCharacterController::PlayerShotStart()
{
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket"))) {
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);
		p2PlayerCharacter->getPlayerCamera()->ChangeView(PlayerViewState::View_SHOT);
	}
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SHIELD, TEXT("LeftArmGardSocket"))) {
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHIELD);
	}
}

void APlayerCharacterController::PlayerShotEnd()
{
	GetWorldSettings()->SetTimeDilation(1.0f);
	p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
	IsShoot = false;
	p2PlayerCharacter->getPlayerCamera()->ChangeView(PlayerViewState::View_IDLE);
	p2PlayerCharacter->getPlayerUI()->SetPlayerAim(false);
	PlayerWeapon->ShowArrowLocationRotation(FVector::ZeroVector, FRotator::ZeroRotator, CanShootArrow);
}

void APlayerCharacterController::PlayerAttackStart()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT) && CanShootArrow) {
		ShootArrow();
		CanShootArrow = false;
		IsShoot = false;
		PlayerShotEnd();
		p2PlayerCharacter->getPlayerUI()->SetPlayerAim(false);
	}
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SWORD, TEXT("RightHandSocket"))) {
		if (p2PlayerSate->CheckCurState(E_PlayerState::Player_SHIELD)) {
			if (p2PlayerSate->getCounterPossibility() && !p2PlayerSate->getCounterAttackValue()) {
				p2PlayerSate->setCounterPossibility(false);
				p2PlayerSate->setCounterAttackValue(true);
			}
		}
		else {
			p2PlayerSate->setPlayerState(E_PlayerState::Player_SWORD);
		}
	}
}

void APlayerCharacterController::PlayerHurt()
{
	if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHIELD)) {
		p2PlayerSate->setPlayerCurHP(-1);
	}
}

void APlayerCharacterController::ShootArrow()
{
	p2PlayerCharacter->getPlayerCamera()->CameraVector();
	FVector ArrowLocation = p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh()->GetSocketLocation(TEXT("LeftHandSocket"));
	FRotator ArrowRotator = p2PlayerCharacter->getPlayerCamera()->GetForwardVector().Rotation() + FRotator(0.0f, -90.0f, 90.0f);;
	FVector ArrowForward = p2PlayerCharacter->getPlayerCamera()->GetForwardVector();

	PlayerWeapon->FireArrow(ArrowLocation, ArrowRotator, ArrowForward);
}

void APlayerCharacterController::WeaponToIdleTimer()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE)) {
		WeaponIdleTime--;
	}
	else {
		WeaponIdleTime = 5;
	}
	if (WeaponIdleTime <= 0)
	{
		GetWorldTimerManager().ClearTimer(AttackTimerHandle);
		WeaponChangeIDLE();
	}
}

void APlayerCharacterController::WeaponToIdle()
{
	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &APlayerCharacterController::WeaponToIdleTimer, 1.0f, true, 0.0f);
	WeaponIdleTime = 5;
}

void APlayerCharacterController::WeaponChangeIDLE()
{
	IsBattle = false;
	CanShootArrow = false;
	IsShoot = false;
	IsSword = false;
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket"))) {
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);
	}
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SWORD, TEXT("RightHandSocket"))) {
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SWORD);
	}

}

void APlayerCharacterController::WeaponChangeSword()
{
	WeaponToIdle();
	IsBattle = true;
	CanShootArrow = false;
	IsShoot = false;
	if (!PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SWORD, TEXT("RightHandSocket")) && PlayerWeapon->getPlayerSwordList().Num() > 0) {
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_SWORD, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("RightHandSocket"));
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SWORD);
	}
	if (!PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SHIELD, TEXT("LeftArmGardSocket")) && PlayerWeapon->getPlayerShieldList().Num() > 0) {
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_SHIELD, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftArmGardSocket"));
	}
}

void APlayerCharacterController::WeaponChangeBow()
{
	IsBattle = true;
	WeaponToIdle();
	if (!PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket"))&& PlayerWeapon->getPlayerBowList().Num()>0) {
		IsBattle = true;
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftHandSocket"));
		if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE) ||
			p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) ||
			p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
			p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);

		}
	}

}

void APlayerCharacterController::PlayerExtraState()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_Carry)) {
		PlayerTrace->ThrowObject();
	}
	else if (p2PlayerSate->getPlayerExtraState() != E_PlayerState::Player_NONE) {
		p2PlayerSate->setExtraState();
	}
}

void APlayerCharacterController::CounterAttackEnemy()
{
	PlayerTrace->PlayerCounterAttack(p2PlayerCharacter->GetActorLocation(), p2PlayerCharacter->GetActorForwardVector(), p2PlayerCharacter);
}

void APlayerCharacterController::PlayerWeaponChangeLeft()
{
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket"))) 
	{
		IsBattle = true;
		WeaponToIdle();
		IsShoot = false;
		PlayerWeapon->ChangeWeapon(E_Weapon::Weapon_BOW,false);
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftHandSocket"));
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);
	}
	else if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SWORD, TEXT("RightHandSocket")))
	{
		PlayerWeapon->ChangeWeapon(E_Weapon::Weapon_SWORD, false); 
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_SWORD, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("RightHandSocket"));
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SWORD);
	}
}

void APlayerCharacterController::PlayerWeaponChangeRight()
{
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket")))
	{
		IsBattle = true;
		WeaponToIdle();
		IsShoot = false;
		PlayerWeapon->ChangeWeapon(E_Weapon::Weapon_BOW, true);
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftHandSocket"));
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);
	}
	else if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SWORD, TEXT("RightHandSocket")))
	{
		PlayerWeapon->ChangeWeapon(E_Weapon::Weapon_SWORD, true);
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_SWORD, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("RightHandSocket"));
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SWORD);
	}
}
