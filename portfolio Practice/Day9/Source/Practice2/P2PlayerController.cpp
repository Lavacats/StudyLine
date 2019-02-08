// Fill out your copyright notice in the Description page of Project Settings.

#include "P2PlayerController.h"

AP2PlayerController::AP2PlayerController()
{
	PlayerTrace = CreateDefaultSubobject<APlayerTrace>(TEXT("PlayerTrace"));
	IsJump = false;
	playerSpeed = 0.5f;
	playerCurSpeed = playerSpeed;
}

void AP2PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	KeyDownCheck();
	PlayerJumpCheck();
	PlayerTraceCheck();
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
		if (p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)){
			p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
		}
	}
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
		p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
	}
	p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue * playerCurSpeed);
}

void AP2PlayerController::LeftRight(float NewAxisValue)
{
	if (p2PlayerCharacter->GetMovementComponent()->IsMovingOnGround()) {
		p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
	}
	p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue * playerCurSpeed);
	
}

void AP2PlayerController::LookUpDown(float NewAxisValue)
{
	float LookPitch = GetControlRotation().Pitch;
	float PitchMin = 330.0f;
	float PitchMax = 5.0f;
	if (LookPitch >= PitchMin || LookPitch <= PitchMax)
	{
		LookPitch += NewAxisValue;
		if (LookPitch >= PitchMin || LookPitch <= PitchMax) {
			SetControlRotation(FRotator(LookPitch, GetControlRotation().Yaw, GetControlRotation().Roll));
		}
	}
}

void AP2PlayerController::Turn(float NewAxisValue)
{
	p2PlayerCharacter->AddControllerYawInput(NewAxisValue);
	
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

void AP2PlayerController::PlayerTraceCheck()
{
	static bool PlayerPush = false;
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_PUSH) || p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) || p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
		PlayerTrace->PlayerTraceCheck(p2PlayerCharacter->GetActorLocation(), p2PlayerCharacter->GetActorForwardVector(), p2PlayerCharacter);
		if (PlayerTrace->getTracePush() && PlayerTrace->getTraceForward() && !PlayerPush) {
			p2PlayerSate->setPlayerState(E_PlayerState::Player_PUSH);
			p2PlayerCharacter->GetMesh()->SetRelativeLocation(FVector(-15.0f, 0, -32.0f));
			PlayerPush = true;
		}
		else if (!PlayerTrace->getTracePush() && !PlayerTrace->getTraceForward() && PlayerPush) {
			p2PlayerSate->setPlayerState(p2PlayerSate->getPrePlayerState());
			p2PlayerCharacter->GetMesh()->SetRelativeLocation(FVector(0, 0, -32.0f));
			PlayerPush = false;
		}
	}
}
