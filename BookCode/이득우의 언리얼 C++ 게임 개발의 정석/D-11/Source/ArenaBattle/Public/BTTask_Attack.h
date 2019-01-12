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
	// ���� �׽�ũ�� ���� �ִϸ��̼��� ���� �� ���� ����ؾ��ϴ� �½�ũ
	// InProgress�� ��ȯ�Ѵ�
	
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
	// ExecuteTask�� ��ȯ�ϴ� �Լ�
	// Aborted: �����߿� �ߴܵǾ���.
	// Failed : �����ߴ�
	// Succeeded : ���������� �����ߴ�
	// InProgress : ���� �������̴�.

private:
	bool IsAttacking = false;

};
