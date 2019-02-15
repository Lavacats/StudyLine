// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
#include "P2PlayerController.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	IsInAir = false;
	IsJump = false;
	IsMove = false;
	IsShoot = false;
	IsClimming = false;
	NextComboCheck = false;
	IsAttacking = false;
	IsComboInputOn = false;
	IsMouseButtonDoun = false;

	CurComboCount = 0;
	MaxComboCount = 3;
	InputComboCount = 0;
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
			if (!IsMouseButtonDoun && PController->getIsSword() && PlayerState->CheckCurState(E_PlayerState::Player_SWORD) && PController->IsInputKeyDown(EKeys::LeftMouseButton)) {
				ABLOG(Warning, TEXT("StartMontage"));
				IsAttacking = true;
				PlayerComboAttack();
				IsMouseButtonDoun = true;
			}
			else if(!PController->IsInputKeyDown(EKeys::LeftMouseButton))
			{
				//IsAttacking = false;
				IsMouseButtonDoun = false;
			}
		}
	}
}


void UPlayerAnimInstance::PlayerComboAttack()
{
	if (IsComboInputOn) {
		if (IsAttacking) {
			if (CurComboCount < MaxComboCount)CurComboCount++;
		}
		else {
			CurComboCount = 0;
			IsComboInputOn = false;
		}
	}
}

void UPlayerAnimInstance::AnimNotify_NextAttackCheck()
{

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
