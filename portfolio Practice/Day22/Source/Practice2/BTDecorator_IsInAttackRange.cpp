// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_IsInAttackRange.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "EnemyState.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetKey));
	if (nullptr == Target)
		return false;

	auto EnemyCharacter = Cast<AEnemyCharacter>(ControllingPawn);
	if (nullptr == EnemyCharacter)
		return false;

	auto State = EnemyCharacter->getEnemyState();
	if (nullptr == State)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= State->getEnemyAttackRange());
	return bResult;
}
