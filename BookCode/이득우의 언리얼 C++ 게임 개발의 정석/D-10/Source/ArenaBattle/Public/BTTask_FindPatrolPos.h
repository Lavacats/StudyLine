// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UBTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	// ExecuteTask가 반환하는 함수
	// Aborted: 실쟁중에 중단되었다.
	// Failed : 실패했다
	// Succeeded : 성공적으로 수행했다
	// InProgress : 현재 수행중이다.
	
};
