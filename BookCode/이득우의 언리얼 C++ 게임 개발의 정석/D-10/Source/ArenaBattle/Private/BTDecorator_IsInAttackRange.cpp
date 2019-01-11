// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_IsInAttackRange.h"
#include "ABAIController.h"
#include "ABCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
	// NodeNaem �� CanAttack���� �д�.
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	// Pawn�� ������ AI���� �����´�.

	if (nullptr == ControllingPawn)
		return false;
	// ���� ���� ��� �Լ��� ������

	auto Target = Cast<AABCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AABAIController::TargetKey));
	// BlackBoard���� Target�� ������ �����´�.
	if (nullptr == Target)
		return false;
	// Target�� ���� ��� �Լ��� ������.

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	// Target���� �Ÿ��� 200�Ʒ��̸� ���� �ƴϸ� ������ bResult�� ��´�.
	return bResult;
}
