// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BT_Decorator_OnAttack.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API UBT_Decorator_OnAttack : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBT_Decorator_OnAttack();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
	
};
