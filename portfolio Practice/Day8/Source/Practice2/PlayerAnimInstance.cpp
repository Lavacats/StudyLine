// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
UPlayerAnimInstance::UPlayerAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (::IsValid(Pawn)) {
		auto data = Cast< APlayerCharacter>(Pawn);
		CurrentPawnSpeed =Pawn->GetVelocity().Size();

		auto Character = Cast<ACharacter>(Pawn);
		if (Character) {
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}
