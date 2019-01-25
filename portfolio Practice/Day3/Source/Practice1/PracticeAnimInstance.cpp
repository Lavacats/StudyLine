// Fill out your copyright notice in the Description page of Project Settings.

#include "PracticeAnimInstance.h"
#include "Practice1Character.h"

UPracticeAnimInstance::UPracticeAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	SetMeshPartsOfPlayer(AnimationPats::Animation_Fase);
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

void UPracticeAnimInstance::AnimNotify_ChestOpenEND()
{
	//if (EAnimMeshParts == AnimationPats::Animation_Fase) {
		ECollectState = E_PlayerCollect::Collect_NONE;
		auto Pawn = TryGetPawnOwner();
		auto data = Cast< APractice1Character>(Pawn);
		data->EndCollect();
	//}
}

void UPracticeAnimInstance::SetCollectState(E_PlayerCollect Collect)
{
	ECollectState = Collect;
}

void UPracticeAnimInstance::SetMeshPartsOfPlayer(AnimationPats Parts)
{
	 EAnimMeshParts = Parts;
}


