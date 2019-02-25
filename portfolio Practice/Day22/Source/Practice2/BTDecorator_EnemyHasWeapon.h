// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_EnemyHasWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API UBTDecorator_EnemyHasWeapon : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_EnemyHasWeapon();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
	
};
