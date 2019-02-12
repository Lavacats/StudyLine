// Fill out your copyright notice in the Description page of Project Settings.

#include "P2PlayerController.h"
#include "PlayerCamera.h"

AP2PlayerController::AP2PlayerController()
{
	PlayerTrace = CreateDefaultSubobject<APlayerTrace>(TEXT("PlayerTrace"));
	PlayerWeapon = CreateDefaultSubobject<APlayerWeapon>(TEXT("PlayerWeapon"));
	CurArrrow = CreateDefaultSubobject<AWeapon_Arrow>(TEXT("CurArrrow"));
	IsJump = false;
	IsMove = false;
	IsClimming = false;
	IsShoot = false;
	playerSpeed = 0.5f;
	playerCurSpeed = playerSpeed;
}

void AP2PlayerController::BeginPlay()
{
	Super::BeginPlay();
	PlayerWeapon = GetWorld()->SpawnActor<APlayerWeapon>( FVector::ZeroVector, FRotator::ZeroRotator);
	PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("BackWaistSocket"));
	PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_ARROW_BAG, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("BackWaistSocket"));
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
			if(!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT))p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
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
		p2PlayerSate->CheckState_And_setState(E_PlayerState::Player_IDLE, E_PlayerState::Player_WALK);
	}
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_CLIMING)){
		p2PlayerCharacter->SetActorLocation(p2PlayerCharacter->GetActorLocation() + p2PlayerCharacter->GetActorUpVector()*playerCurSpeed*NewAxisValue*0.5f);
	}
	else if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {
		p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue * playerCurSpeed);
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
		p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue * playerCurSpeed);
	}
}

void AP2PlayerController::LookUpDown(float NewAxisValue)
{
	float LookPitch = GetControlRotation().Pitch;
	float PitchMin = 330.0f;
	float PitchMax = 5.0f;
	if (LookPitch >= PitchMin || LookPitch <= PitchMax){
		LookPitch += NewAxisValue;
		if (LookPitch >= PitchMin || LookPitch <= PitchMax) {
			SetControlRotation(FRotator(LookPitch, GetControlRotation().Yaw, GetControlRotation().Roll));
		}
	}
}

void AP2PlayerController::Turn(float NewAxisValue)
{
	static bool shotCheck = false;
	static float rotationValue = 0.0f;
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_SHOT)) {

		//CurArrrow->SetActorRelativeRotation(FRotator(GetControlRotation().Pitch, GetControlRotation().Yaw, GetControlRotation().Roll));
		if (!shotCheck) {
			rotationValue = GetControlRotation().Yaw;
			p2PlayerCharacter->SetActorRotation(FRotator(p2PlayerCharacter->GetActorRotation().Pitch, GetControlRotation().Yaw, p2PlayerCharacter->GetActorRotation().Roll));
			shotCheck = true;
		}
		
		float LookYaw = GetControlRotation().Yaw;
		float YawMin = rotationValue - 45.0f;
		float YawMax = rotationValue + 45.0f;
		if (LookYaw >= YawMin && LookYaw <= YawMax) {
			LookYaw += NewAxisValue;
			if (LookYaw >= YawMin && LookYaw <= YawMax) {
				SetControlRotation(FRotator(GetControlRotation().Pitch, LookYaw, GetControlRotation().Roll));
			}
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
		//p2PlayerCharacter->AddActorLocalOffset(p2PlayerCharacter->GetActorForwardVector()*2.0f);
	}
}

void AP2PlayerController::PlayerShotStart()
{
	if(!PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW,TEXT("LeftHandSocket"))){
		IsBattle = true;
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftHandSocket"));
	}
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE) ||
		p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) ||
		p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);
		p2PlayerCharacter->getPlayerCamera()->ChangeView(PlayerViewState::View_SHOT);
		
		SpawnArrow();
	}
}

void AP2PlayerController::PlayerShotEnd()
{
	p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
	IsShoot = false;
	p2PlayerCharacter->getPlayerCamera()->ChangeView(PlayerViewState::View_IDLE);
}

void AP2PlayerController::PlayerAttackStart()
{
	IsBattle = false;
	IsShoot = false;
	p2PlayerCharacter->getPlayerCamera()->ChangeView(PlayerViewState::View_IDLE);


}

void AP2PlayerController::SpawnArrow()
{
	CurArrrow = PlayerWeapon->getArrow();
	//CurArrrow->AttachToComponent(p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("LeftHandSocket"));
	CurArrrow->SetActorRelativeLocation(p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh()->GetSocketLocation("LeftHandSocket"));
	CurArrrow->SetActorRelativeLocation(FVector(CurArrrow->GetActorLocation().X, CurArrrow->GetActorLocation().Y, CurArrrow->GetActorLocation().Z + 100.0f));
	CurArrrow->SetActorRelativeRotation(FRotator(0.0f, 270.0f, 00.0f));
}

void AP2PlayerController::ShootArrow()
{
}
