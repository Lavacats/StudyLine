// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "P2PlayerState.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float curSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsJump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsMove;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsClimming;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsBattle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	AP2PlayerState* p2PlayerState;


public:
	UPlayerAnimInstance();
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	//void serPlayerState(AP2PlayerState* state) { p2PlayerState = state; }

private:
	UFUNCTION()
		void AnimNotify_JumpStartFinish();
	UFUNCTION()
		void AnimNotify_JumpEnd();
	UFUNCTION()
		void AnimNotify_StartBow();
	UFUNCTION()
		void AnimNotify_EndBow();
};
