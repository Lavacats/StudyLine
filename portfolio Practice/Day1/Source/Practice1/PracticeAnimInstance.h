// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice1.h"
#include "Animation/AnimInstance.h"
#include "PracticeAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE1_API UPracticeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPracticeAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;
	
};
