// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EnemyFindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API UBTTask_EnemyFindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_EnemyFindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	
	
};
