// Fill out your copyright notice in the Description page of Project Settings.

#include "P2PlayerController.h"
#include "PlayerCamera.h"

#include "DrawDebugHelpers.h"

AP2PlayerController::AP2PlayerController()
{
	PlayerTrace = CreateDefaultSubobject<APlayerTrace>(TEXT("PlayerTrace"));
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

void AP2PlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerWeapon = GetWorld()->SpawnActor<APlayerWeapon>( FVector::ZeroVector, FRotator::ZeroRotator);
	PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("PlayerBackStorage"));
	PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_ARROW_BAG, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("BackWaistSocket"));
	PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_SWORD_SHEATH, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftUpLegSocket"));
}

void AP2PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	KeyDownCheck();
	PlayerJumpCheck();
	PlayerTrace->PlayerTraceCheck(p2PlayerCharacter->GetActorLocation(), p2PlayerCharacter->GetActorForwardVector(), p2PlayerCharacter);
	PlayerTracePushCheck();
	PlayerTraceClimmingCheck();
}

void AP2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("MoveForwardBack"), this, &AP2PlayerController::ForwardBack);
	InputComponent->BindAxis(TEXT("MoveLeftRight"), this, &AP2PlayerController::LeftRight);
	InputComponent->BindAxis(TEXT("Turn"), this, &AP2PlayerController::Turn);
	InputComponent->BindAxis(TEXT("LookUpDown"), this, &AP2PlayerController::LookUpDown);
	
	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AP2PlayerController::PlayerJump);
	InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &AP2PlayerController::PlayerRunStart);
	InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &AP2PlayerController::PlayerRunStop);
	InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &AP2PlayerController::PlayerCrouch);
	InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &AP2PlayerController::PlayerUnCrouch);

	InputComponent->BindAction(TEXT("Shot"), EInputEvent::IE_Pressed, this, &AP2PlayerController::PlayerShotStart);
	InputComponent->BindAction(TEXT("Shot"), EInputEvent::IE_Released, this, &AP2PlayerController::PlayerShotEnd);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AP2PlayerController::PlayerAttackStart);

	InputComponent->BindAction(TEXT("WeaponChange1"), EInputEvent::IE_Pressed, this, &AP2PlayerController::WeaponChangeIDLE);
	InputComponent->BindAction(TEXT("WeaponChange2"), EInputEvent::IE_Pressed, this, &AP2PlayerController::WeaponChangeSword);
	InputComponent->BindAction(TEXT("WeaponChange3"), EInputEvent::IE_Pressed, this, &AP2PlayerController::WeaponChangeBow);
	InputComponent->BindAction(TEXT("Press4"), EInputEvent::IE_Pressed, this, &AP2PlayerController::PlayerHurt);
	
	InputComponent->BindAction(TEXT("ExtraInput"), EInputEvent::IE_Pressed, this, &AP2PlayerController::PlayerExtraState);

}

void AP2PlayerController::Possess(APawn * aPawn)
{
	Super::Possess(aPawn);
	if (aPawn) {
		p2PlayerCharacter = Cast< APlayerCharacter>(aPawn);
		p2PlayerSate = Cast< AP2PlayerState>(PlayerState);

	}
}

void AP2PlayerController::KeyDownCheck()
{
	if (!IsInputKeyDown(EKeys::W) && !IsInputKeyDown(EKeys::S) && !IsInputKeyDown(EKeys::A) && !IsInputKeyDown(EKeys::D)) {
		if (p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN) ){
			if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {
				p2PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
			}
		}
		IsMove = false;
	}
	playerCurSpeed = playerSpeed;
}

void AP2PlayerController::PlayerJumpCheck()
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

void AP2PlayerController::ForwardBack(float NewAxisValue)
{
	if (p2PlayerCharacter->GetMovementComponent()->IsMovingOnGround()) {
		{
			p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
		}
	}
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING)){
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorUpVector()*playerCurSpeed*NewAxisValue*0.5f);
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {
		if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SHIELD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD)&& !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT)&& !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
			p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue * playerCurSpeed);
		}
	
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
		//p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue * playerCurSpeed*0.3f);
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorForwardVector()*playerCurSpeed*NewAxisValue*0.5f);
	}
	IsMove = true;
}

void AP2PlayerController::LeftRight(float NewAxisValue)
{
	if (p2PlayerCharacter->GetMovementComponent()->IsMovingOnGround()) {
		p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
	}
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING)) {
		if (IsMove)p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorRightVector()*playerCurSpeed*NewAxisValue);
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {
		if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SHIELD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD)&& !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
			p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue * playerCurSpeed);
		}
		
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorRightVector()*playerCurSpeed*NewAxisValue*0.5f);
	}
}

void AP2PlayerController::LookUpDown(float NewAxisValue)
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
	else{
		p2PlayerCharacter->AddControllerPitchInput(-NewAxisValue);
	}
}

void AP2PlayerController::Turn(float NewAxisValue)
{
	static bool shotCheck = false;
	static float rotationValue = 0.0f;
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {

		static float LookYaw = 0.0f;

		if (!shotCheck && (p2PlayerCharacter->getPlayerCamera()->getPlayerViewState()== PlayerViewState::View_SHOT)) {
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

void AP2PlayerController::PlayerJump()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE) || p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
		p2PlayerCharacter->Jump();
		IsJump = true;
	}
}

void AP2PlayerController::PlayerRunStart()
{
	p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_WALK, E_PlayerState::Player_RUN);
	playerCurSpeed =playerSpeed* 1.5f;
}

void AP2PlayerController::PlayerRunStop()
{
	p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_RUN, E_PlayerState::Player_WALK);
	playerCurSpeed = playerSpeed;
}

void AP2PlayerController::PlayerCrouch()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE) ||
		p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) ||
		p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) 
	{
		p2PlayerSate->setPlayerState(E_PlayerState::Player_CROUCH);
		p2PlayerCharacter->Crouch();
	}
}

void AP2PlayerController::PlayerUnCrouch()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CROUCH)) {
		p2PlayerCharacter->UnCrouch();
		p2PlayerSate->setPlayerState(p2PlayerSate->getPrePlayerState());
	}
}

void AP2PlayerController::PlayerTracePushCheck()
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

void AP2PlayerController::PlayerTraceClimmingCheck()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING) || p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN) || p2PlayerSate->CheckCurState(E_PlayerState::Player_JUMP)) {
		if (PlayerTrace->getTraceHeight() && PlayerTrace->getTraceClimming() && PlayerTrace->getTraceClose() && PlayerTrace->getTraceForward() && !IsClimming ) {
			p2PlayerSate->setPlayerState(E_PlayerState::Player_CLIMING);
			p2PlayerCharacter->GetCharacterMovement()->StopMovementImmediately();
			p2PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			IsClimming = true;
		}
		else if (!PlayerTrace->getTraceHeight() && PlayerTrace->getTraceClimming() && PlayerTrace->getTraceClose() && PlayerTrace->getTraceForward()  && IsClimming){
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
	if(p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING) && !IsClimming) {
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation()+p2PlayerCharacter->GetActorUpVector()*0.75f);
	}
}

void AP2PlayerController::PlayerShotStart()
{
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket"))) {
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);
		p2PlayerCharacter->getPlayerCamera()->ChangeView(PlayerViewState::View_SHOT);
	//	GetWorldSettings()->SetTimeDilation(0.75f);
	}
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SHIELD, TEXT("LeftArmGardSocket"))) {
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHIELD);
	}
}

void AP2PlayerController::PlayerShotEnd()
{
	GetWorldSettings()->SetTimeDilation(1.0f);
	p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
	IsShoot = false;
	p2PlayerCharacter->getPlayerCamera()->ChangeView(PlayerViewState::View_IDLE);
	p2PlayerCharacter->getPlayerCamera()->PlayerAimOnOff(false);
	PlayerWeapon->ShowArrowLocationRotation(FVector::ZeroVector, FRotator::ZeroRotator, CanShootArrow);
}

void AP2PlayerController::PlayerAttackStart()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT) && CanShootArrow) {
		ShootArrow();
		CanShootArrow = false;
		IsShoot = false;
		PlayerShotEnd();
		p2PlayerCharacter->getPlayerCamera()->PlayerAimOnOff(false);
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

void AP2PlayerController::PlayerHurt()
{
	if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHIELD)) {
		p2PlayerSate->setPlayerCurHP(-1);
	}
}

void AP2PlayerController::ShootArrow()
{
	p2PlayerCharacter->getPlayerCamera()->CameraVector();
	FVector ArrowLocation = p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh()->GetSocketLocation(TEXT("LeftHandSocket"));
	FRotator ArrowRotator = p2PlayerCharacter->getPlayerCamera()->GetForwardVector().Rotation() + FRotator(0.0f, -90.0f, 90.0f);;
	FVector ArrowForward = p2PlayerCharacter->getPlayerCamera()->GetForwardVector();

	PlayerWeapon->FireArrow(ArrowLocation, ArrowRotator, ArrowForward);
}

void AP2PlayerController::WeaponToIdleTimer()
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

void AP2PlayerController::WeaponToIdle()
{
	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AP2PlayerController::WeaponToIdleTimer, 1.0f, true, 0.0f);
	WeaponIdleTime = 5;
}

void AP2PlayerController::WeaponChangeIDLE()
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

void AP2PlayerController::WeaponChangeSword()
{
	WeaponToIdle();
	IsBattle = true;
	CanShootArrow = false;
	IsShoot = false;
	if (!PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SWORD, TEXT("RightHandSocket"))) {
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_SWORD, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("RightHandSocket"));
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SWORD);
	}
	if (!PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SHIELD, TEXT("LeftArmGardSocket"))) {
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_SHIELD, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftArmGardSocket"));
	}
}

void AP2PlayerController::WeaponChangeBow()
{
	IsBattle = true;
	WeaponToIdle();
	if (!PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket"))) {
		IsBattle = true;
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftHandSocket"));
		if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE) ||
			p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) ||
			p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {

			p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);

		}
	}

}

void AP2PlayerController::PlayerExtraState()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_Carry)) {
		PlayerTrace->ThrowObject();
	}
	else if (p2PlayerSate->getPlayerExtraState() != E_PlayerState::Player_NONE) {
		p2PlayerSate->setExtraState();
	}
}

void AP2PlayerController::CounterAttackEnemy()
{
	PlayerTrace->PlayerCounterAttack(p2PlayerCharacter->GetActorLocation(), p2PlayerCharacter->GetActorForwardVector(), p2PlayerCharacter);
}
