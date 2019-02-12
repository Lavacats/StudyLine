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
	//if (PlayerState->CheckCurState(E_PlayerState::Player_SHOT)) {
	{
		Cast<AP2PlayerController>(PlayerController)->setIsShoot(true);

		//PlayerState->setPlayerState(PlayerState->getPrePlayerState());
	}
}

void UPlayerAnimInstance::AnimNotify_EndBow()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PlayerState = Cast<AP2PlayerController>(PlayerController)->getPlayerState();
	auto Pawn = TryGetPawnOwner();
	auto Character = Cast<APlayerCharacter>(Pawn);
	//if (PlayerState->CheckCurState(E_PlayerState::Player_SHOT)) {
	{
		PlayerState->setPlayerState(PlayerState->getPrePlayerState());
		Cast<AP2PlayerController>(PlayerController)->getPlayerWeapon()->setWeaponComponent(E_Weapon::Weapon_BOW,Character->getPlayerMeshComponent()->getRootMesh(),TEXT("BackWaistSocket"));
	}
}
