// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacterBattleController.h"

APlayerCharacterBattleController::APlayerCharacterBattleController()
{
	IsBattle = true;
	IsShoot = false;
	IsSword = false;
	CanShootArrow = false;
	WeaponIdleTime = 5;
}

void APlayerCharacterBattleController::PlayerBattleSetting(APlayerCharacter * Character, UPlayerCharacterState * Sate, UPlayerTrace* Trace)
{
	p2PlayerCharacter= Character;
	p2PlayerSate= Sate;
	PlayerTrace = Trace;
}

void APlayerCharacterBattleController::BeginPlay()
{
	Super::BeginPlay();
	PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("PlayerBackStorage"));
	PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_ARROW_BAG, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("BackWaistSocket"));

}

void APlayerCharacterBattleController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacterBattleController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void APlayerCharacterBattleController::PlayerShotStart()
{
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket"))) {
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);
		p2PlayerCharacter->getPlayerCamera()->ChangeView(PlayerViewState::View_SHOT);
	}
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SHIELD, TEXT("LeftArmGardSocket"))) {
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHIELD);
	}
}

void APlayerCharacterBattleController::PlayerShotEnd()
{
	GetWorldSettings()->SetTimeDilation(1.0f);
	p2PlayerSate->setPlayerState(E_PlayerState::Player_IDLE);
	IsShoot = false;
	p2PlayerCharacter->getPlayerCamera()->ChangeView(PlayerViewState::View_IDLE);
	p2PlayerCharacter->getPlayerUI()->SetPlayerAim(false);
	PlayerWeapon->ShowArrowLocationRotation(FVector::ZeroVector, FRotator::ZeroRotator, CanShootArrow);
}

void APlayerCharacterBattleController::PlayerAttackStart()
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

void APlayerCharacterBattleController::PlayerHurt()
{
	if (!p2PlayerSate->CheckCurState(E_PlayerState::Player_SHIELD)) {
		p2PlayerSate->setPlayerCurHP(-1);
	}
}

void APlayerCharacterBattleController::ShootArrow()
{
	p2PlayerCharacter->getPlayerCamera()->CameraVector();
	FVector ArrowLocation = p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh()->GetSocketLocation(TEXT("LeftHandSocket"));
	FRotator ArrowRotator = p2PlayerCharacter->getPlayerCamera()->GetForwardVector().Rotation() + FRotator(0.0f, -90.0f, 90.0f);;
	FVector ArrowForward = p2PlayerCharacter->getPlayerCamera()->GetForwardVector();

	PlayerWeapon->FireArrow(ArrowLocation, ArrowRotator, ArrowForward);
}

void APlayerCharacterBattleController::WeaponToIdleTimer()
{
	if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE)) {
		WeaponIdleTime--;
	}
	else {
		WeaponIdleTime = 5;
	}
	if (WeaponIdleTime <= 0){
		GetWorldTimerManager().ClearTimer(AttackTimerHandle);
		WeaponChangeIDLE();
	}
}

void APlayerCharacterBattleController::WeaponToIdle()
{
	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &APlayerCharacterBattleController::WeaponToIdleTimer, 1.0f, true, 0.0f);
	WeaponIdleTime = 5;
}

void APlayerCharacterBattleController::WeaponChangeIDLE()
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

void APlayerCharacterBattleController::WeaponChangeSword()
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

void APlayerCharacterBattleController::WeaponChangeBow()
{
	IsBattle = true;
	WeaponToIdle();
	if (!PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket")) && PlayerWeapon->getPlayerBowList().Num() > 0) {
		IsBattle = true;
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftHandSocket"));
		if (p2PlayerSate->CheckCurState(E_PlayerState::Player_IDLE) ||
			p2PlayerSate->CheckCurState(E_PlayerState::Player_WALK) ||
			p2PlayerSate->CheckCurState(E_PlayerState::Player_RUN)) {
			p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);
		}
	}
}

void APlayerCharacterBattleController::CounterAttackEnemy()
{
	PlayerTrace->PlayerCounterAttack(p2PlayerCharacter->GetActorLocation(), p2PlayerCharacter->GetActorForwardVector(), p2PlayerCharacter);
}

void APlayerCharacterBattleController::PlayerWeaponChangeLeft()
{
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket"))){
		IsBattle = true;
		WeaponToIdle();
		IsShoot = false;
		PlayerWeapon->ChangeWeapon(E_Weapon::Weapon_BOW, false);
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftHandSocket"));
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);
	}
	else if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SWORD, TEXT("RightHandSocket"))){
		PlayerWeapon->ChangeWeapon(E_Weapon::Weapon_SWORD, false);
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_SWORD, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("RightHandSocket"));
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SWORD);
	}

	p2PlayerCharacter->getPlayerUI()->SetHP(12, --hpvalue);
}

void APlayerCharacterBattleController::PlayerWeaponChangeRight()
{
	if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_BOW, TEXT("LeftHandSocket"))) {
		IsBattle = true;
		WeaponToIdle();
		IsShoot = false;
		PlayerWeapon->ChangeWeapon(E_Weapon::Weapon_BOW, true);
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_BOW, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftHandSocket"));
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SHOT);
	}
	else if (PlayerWeapon->checkParentComponent(E_Weapon::Weapon_SWORD, TEXT("RightHandSocket"))) {
		PlayerWeapon->ChangeWeapon(E_Weapon::Weapon_SWORD, true);
		PlayerWeapon->setWeaponComponent(E_Weapon::Weapon_SWORD, p2PlayerCharacter->getPlayerMeshComponent()->getRootMesh(), TEXT("RightHandSocket"));
		p2PlayerSate->setPlayerState(E_PlayerState::Player_SWORD);
	}
	p2PlayerCharacter->getPlayerUI()->SetHP(12, ++hpvalue);
}
