// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Decorator_OnAttack.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_Decorator_OnAttack::UBT_Decorator_OnAttack()
{
	NodeName = TEXT("EnemyOnAttack");
}

bool UBT_Decorator_OnAttack::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto EnemyCharacter = Cast<AEnemyCharacter>(ControllingPawn);
	if (nullptr == EnemyCharacter)
		return false;


	return EnemyCharacter->getOnBattle();
}
