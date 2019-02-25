// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "MyBTDecorator_Blackboard.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API UMyBTDecorator_Blackboard : public UBTDecorator_Blackboard
{
	GENERATED_BODY()
public:
	UMyBTDecorator_Blackboard();
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
	
};
