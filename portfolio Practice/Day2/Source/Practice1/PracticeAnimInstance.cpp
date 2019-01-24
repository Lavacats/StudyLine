// Fill out your copyright notice in the Description page of Project Settings.

#include "PracticeAnimInstance.h"
#include "Practice1Character.h"

UPracticeAnimInstance::UPracticeAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
}

void UPracticeAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	
	if (::IsValid(Pawn)) {
		auto data = Cast< APractice1Character>(Pawn);
		CurrentPawnSpeed = data->getMoveSpeed();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character) {
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

