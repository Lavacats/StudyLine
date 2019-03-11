// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacterController.h"
#include "Player/PlayerCamera.h"
#include "DrawDebugHelpers.h"

APlayerCharacterController::APlayerCharacterController()
{
	PlayerTrace = CreateDefaultSubobject<UPlayerTrace>(TEXT("PlayerTrace"));
	p2PlayerSate = CreateDefaultSubobject<UPlayerCharacterState>(TEXT("p2PlayerSate"));
	PlayerWeapon = CreateDefaultSubobject<APlayerWeapon>(TEXT("PlayerWeapon"));
	MoveController = CreateDefaultSubobject<APlayerChracterMoveController>(TEXT("MoveController"));
	BattleController = CreateDefaultSubobject<APlayerCharacterBattleController>(TEXT("BattleController"));
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	PlayerWeapon = GetWorld()->SpawnActor<APlayerWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	BattleController->setPlayerWeapon(PlayerWeapon);
	BattleController->BeginPlay();
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveController->Tick(DeltaTime);
	BattleController->Tick(DeltaTime);
	KeyDownCheck();
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("MoveForwardBack"), this, &APlayerCharacterController::ForwardBack);
	InputComponent->BindAxis(TEXT("MoveLeftRight"), this, &APlayerCharacterController::LeftRight);
	InputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacterController::Turn);
	InputComponent->BindAxis(TEXT("LookUpDown"), this, &APlayerCharacterController::LookUpDown);

	InputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, MoveController, &APlayerChracterMoveController::PlayerJump);
	InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, MoveController, &APlayerChracterMoveController::PlayerRunStart);
	InputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, MoveController, &APlayerChracterMoveController::PlayerRunStop);
	InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, MoveController, &APlayerChracterMoveController::PlayerCrouch);
	InputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, MoveController, &APlayerChracterMoveController::PlayerUnCrouch);

	InputComponent->BindAction(TEXT("ExtraInput"), EInputEvent::IE_Pressed, MoveController, &APlayerChracterMoveController::PlayerExtraState);

	InputComponent->BindAction(TEXT("Shot"), EInputEvent::IE_Pressed, BattleController, &APlayerCharacterBattleController::PlayerShotStart);
	InputComponent->BindAction(TEXT("Shot"), EInputEvent::IE_Released, BattleController, &APlayerCharacterBattleController::PlayerShotEnd);
	InputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, BattleController, &APlayerCharacterBattleController::PlayerAttackStart);

	InputComponent->BindAction(TEXT("WeaponChange1"), EInputEvent::IE_Pressed, BattleController, &APlayerCharacterBattleController::WeaponChangeIDLE);
	InputComponent->BindAction(TEXT("WeaponChange2"), EInputEvent::IE_Pressed, BattleController, &APlayerCharacterBattleController::WeaponChangeSword);
	InputComponent->BindAction(TEXT("WeaponChange3"), EInputEvent::IE_Pressed, BattleController, &APlayerCharacterBattleController::WeaponChangeBow);

	InputComponent->BindAction(TEXT("WeaponChangeLeft"), EInputEvent::IE_Pressed, BattleController, &APlayerCharacterBattleController::PlayerWeaponChangeLeft);
	InputComponent->BindAction(TEXT("WeaponChangeRight"), EInputEvent::IE_Pressed, BattleController, &APlayerCharacterBattleController::PlayerWeaponChangeRight);
}

void APlayerCharacterController::Possess(APawn * aPawn)
{
	Super::Possess(aPawn);
	if (aPawn) {
		p2PlayerCharacter = Cast< APlayerCharacter>(aPawn);
		MoveController->PlayerMoveSetting(p2PlayerCharacter, p2PlayerSate, PlayerTrace);
		BattleController->PlayerBattleSetting(p2PlayerCharacter, p2PlayerSate, PlayerTrace);
	}
}

void APlayerCharacterController::KeyDownCheck()
{
	if (!IsInputKeyDown(EKeys::W) && !IsInputKeyDown(EKeys::S) && !IsInputKeyDown(EKeys::A) && !IsInputKeyDown(EKeys::D)) {
		MoveController->KeyDownCheck();
	}
}

void APlayerCharacterController::ForwardBack(float NewAxisValue)
{
	if (p2PlayerCharacter->GetMovementComponent()->IsMovingOnGround()) {
		p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
	}
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING)) {
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorUpVector()*MoveController->getCurSpeed()*NewAxisValue*0.5f);
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {
		if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SHIELD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
			p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue * MoveController->getCurSpeed());
		}
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorForwardVector()*MoveController->getCurSpeed()*NewAxisValue*0.5f);
	}
	MoveController->setIsMoveValue(true);
}

void APlayerCharacterController::LeftRight(float NewAxisValue)
{
	if (p2PlayerCharacter->GetMovementComponent()->IsMovingOnGround()) {
		p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
	}
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING)) {
		if (MoveController->getIsMove())p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorRightVector()*MoveController->getCurSpeed()*NewAxisValue);
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {
		if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SHIELD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
			p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue * MoveController->getCurSpeed());
		}
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SWORD) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_HURT) && !p2PlayerSate->CheckCurState(E_PlayerState::Player_DEATH)) {
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorRightVector()*MoveController->getCurSpeed()*NewAxisValue*0.5f);
	}
}

void APlayerCharacterController::LookUpDown(float NewAxisValue)
{
	float LookPitch = GetControlRotation().Pitch;
	float PitchMin = 330.0f;
	float PitchMax = 5.0f;
	if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)){
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
		PlayerWeapon->ShowArrowLocationRotation(p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh()->GetSocketLocation(TEXT("LeftHandSocket")), GetControlRotation(), BattleController->getCanShootArrow());
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

