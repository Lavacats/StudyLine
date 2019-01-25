// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice1.h"
#include "Practice1Character.h"
#include "Animation/AnimInstance.h"
#include "PracticeAnimInstance.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class E_PlayerCollect : uint8 {
	Collect_NONE,
	Collect_BOX
};

UENUM()
enum class AnimationPats : uint8 {
	Animation_Fase,
	Animation_Hair,
	Animation_Upper,
	Animation_down
};

UCLASS()
class PRACTICE1_API UPracticeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPracticeAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void AnimNotify_ChestOpenEND();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collect, Meta = (AllowPrivateAccess = true))
	E_PlayerCollect ECollectState;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collect, Meta = (AllowPrivateAccess = true))
	AnimationPats EAnimMeshParts;
public:
	void SetCollectState(E_PlayerCollect Collect);
	void SetMeshPartsOfPlayer(AnimationPats Parts);
};
