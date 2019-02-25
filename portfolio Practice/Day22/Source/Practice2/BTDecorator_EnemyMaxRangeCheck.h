// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_EnemyMaxRangeCheck.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API UBTDecorator_EnemyMaxRangeCheck : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_EnemyMaxRangeCheck();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};
