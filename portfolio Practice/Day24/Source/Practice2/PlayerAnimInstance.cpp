// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
#include "P2PlayerState.h"
#include "P2PlayerController.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	IsInAir = false;
	IsJump = false;
	IsMove = false;
	IsShoot = false;
	IsClimming = false;
	IsMouseRightButtonDown = false;
	MaxCombo = 3;
	AttackEndComboState();

}

void UPlayerAnimInstance::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);


	StartAttackCollision();
	//ABLOG(Warning, TEXT("Start"));
}

void UPlayerAnimInstance::AttackEndComboState()
{
	if (IsValid(GetWorld())) {
		auto PlayerController = GetWorld()->GetFirstPlayerController();
		if (IsValid(PlayerController))
		{
			auto PController = Cast< AP2PlayerController>(PlayerController);
			auto PlayerState = Cast<AP2PlayerController>(PlayerController)->getPlayerState();
			if (IsValid(PController) && IsValid(PlayerState)) {
				PlayerState->setPlayerState(E_PlayerState::Player_IDLE);
			}
		}
	}

	IsComboInputOn = false;
	CanNextCombo = false;
	IsAttacking = false;
	CurrentCombo = 0;

}

void UPlayerAnimInstance::StartAttackCollision()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (::IsValid(PlayerController)) {
		auto PController = Cast< AP2PlayerController>(PlayerController);
		if ((::IsValid(PController))) {
			auto PlayerSworld = PController->getPlayerWeapon()->getPlayerSworld();
			PlayerSworld->setHitEnemy(true);
		}
	}
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) {
		IsMove = Cast< AP2PlayerController>(PlayerController)->getIsMove();
		IsClimming = Cast< AP2PlayerController>(PlayerController)->getIsClimming();
		IsBattle = Cast< AP2PlayerController>(PlayerController)->getIsBattle();
		IsShoot = Cast< AP2PlayerController>(PlayerController)->getIsShoot();
		auto playerState = Cast< AP2PlayerController>(PlayerController)->getPlayerState();
		if (playerState) {
			p2PlayerState = playerState;
		}
	}

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn)) {
		curSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character) {
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}

	if (IsValid(PlayerController))
	{
		auto PController = Cast< AP2PlayerController>(PlayerController);
		auto PlayerState = Cast<AP2PlayerController>(PlayerController)->getPlayerState();
		if (IsValid(PController) && IsValid(PlayerState)) {
			if (!IsMouseRightButtonDown && PController->getIsSword() && PlayerState->CheckCurState(E_PlayerState::Player_SWORD) && PController->IsInputKeyDown(EKeys::LeftMouseButton)) {
				IsMouseRightButtonDown = true;
				if (IsAttacking) {
					ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
					if (CanNextCombo) {
						IsComboInputOn = true;
					}
				}
				else {
					ABCHECK(CurrentCombo == 0);
					AttackStartComboState();
					IsAttacking = true;
				}
			}
			else if(!PController->IsInputKeyDown(EKeys::LeftMouseButton)){
				IsMouseRightButtonDown = false;
			}
		}
	}
}


void UPlayerAnimInstance::AnimNotify_HurtEnd()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PlayerState = Cast<AP2PlayerController>(PlayerController)->getPlayerState();
	PlayerState->setPlayerState(E_PlayerState::Player_IDLE);
}

void UPlayerAnimInstance::AnimNotify_AttackStart()
{

}

void UPlayerAnimInstance::AnimNotify_NextAttackCheck()
{
	CanNextCombo = false;
	if (IsComboInputOn) {
		AttackStartComboState();
	}
	else {
		AttackEndComboState();
	}
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (::IsValid(PlayerController)) {
		auto PController = Cast< AP2PlayerController>(PlayerController);
		if ((::IsValid(PController))) {
			auto PlayerSworld = PController->getPlayerWeapon()->getPlayerSworld();
			PlayerSworld->setHitEnemy(false);
		}
	}

	StartAttackCollision();
	//ABLOG(Warning, TEXT("Reset"));
}

void UPlayerAnimInstance::AnimNotify_AttackComboEnd()
{
	AttackEndComboState();
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (::IsValid(PlayerController)) {
		auto PController = Cast< AP2PlayerController>(PlayerController);
		if ((::IsValid(PController))) {
			auto PlayerSworld = PController->getPlayerWeapon()->getPlayerSworld();
			PlayerSworld->setHitEnemy(false);
		}
	}
	//ABLOG(Warning, TEXT("Reset"));
}

void UPlayerAnimInstance::AnimNotify_JumpStartFinish()
{
	IsJump = true;
}

void UPlayerAnimInstance::AnimNotify_JumpEnd()
{
	IsJump = false;
}

void UPlayerAnimInstance::AnimNotify_StartBow()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PlayerState = Cast<AP2PlayerController>(PlayerController)->getPlayerState();
	if (PlayerState->CheckCurState(E_PlayerState::Player_SHOT)) {
	
		Cast<AP2PlayerController>(PlayerController)->setIsShoot(true);
		//PlayerState->setPlayerState(PlayerState->getPrePlayerState());
		if (!Cast<AP2PlayerController>(PlayerController)->IsInputKeyDown(EKeys::RightMouseButton)) {
			PlayerState->setPlayerState(PlayerState->getPrePlayerState());
		}
	}
}

void UPlayerAnimInstance::AnimNotify_EndBow()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PlayerState = Cast<AP2PlayerController>(PlayerController)->getPlayerState();
	auto Pawn = TryGetPawnOwner();
	auto Character = Cast<APlayerCharacter>(Pawn);
	if (PlayerState->CheckCurState(E_PlayerState::Player_SHOT)) {
	
		PlayerState->setPlayerState(PlayerState->getPrePlayerState());
		Cast<AP2PlayerController>(PlayerController)->getPlayerWeapon()->setWeaponComponent(E_Weapon::Weapon_BOW,Character->getPlayerMeshComponent()->getRootMesh(),TEXT("BackWaistSocket"));
	}
}

void UPlayerAnimInstance::AnimNotify_StartAIM()
{
	auto PlayerController = Cast<AP2PlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->setCanShootArrow(true);
	PlayerController->getPlayerCharacter()->getPlayerCamera()->PlayerAimOnOff(true);
}

void UPlayerAnimInstance::AnimNotify_DrawSwordEnd()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PlayerState = Cast<AP2PlayerController>(PlayerController)->getPlayerState();

	PlayerState->setPlayerState(E_PlayerState::Player_IDLE);
	Cast<AP2PlayerController>(PlayerController)->setIsSword(true);
}

void UPlayerAnimInstance::AnimNotify_StealthSword()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PlayerState = Cast<AP2PlayerController>(PlayerController)->getPlayerState();
	auto Pawn = TryGetPawnOwner();
	auto Character = Cast<APlayerCharacter>(Pawn);
	if (PlayerState->CheckCurState(E_PlayerState::Player_SWORD)) {

		PlayerState->setPlayerState(PlayerState->getPrePlayerState());
		Cast<AP2PlayerController>(PlayerController)->getPlayerWeapon()->setWeaponComponent(E_Weapon::Weapon_None, Character->getPlayerMeshComponent()->getRootMesh(), TEXT("LeftUpLegSocket"));
	}
}

void UPlayerAnimInstance::AnimNotify_ThrowEnd()
{
	auto Controller = GetWorld()->GetFirstPlayerController();
	AP2PlayerController* PlayerController = Cast<AP2PlayerController>(Controller);
	AP2PlayerState* PlayerState = PlayerController->getPlayerState();
	PlayerState->setThrowObject(false);
	PlayerState->setPlayerState(E_PlayerState::Player_IDLE);
}
