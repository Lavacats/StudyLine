// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ArenaBattle.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	// 공격 테스크는 공격 애니메이션이 끝날 때 까지 대기해야하는 태스크
	// InProgress로 반환한다
	
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
	// ExecuteTask가 반환하는 함수
	// Aborted: 실쟁중에 중단되었다.
	// Failed : 실패했다
	// Succeeded : 성공적으로 수행했다
	// InProgress : 현재 수행중이다.

private:
	bool IsAttacking = false;

};
