// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_EnemyMaxRangeCheck.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "EnemyState.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_EnemyMaxRangeCheck::UBTDecorator_EnemyMaxRangeCheck()
{
	NodeName = TEXT("IsInMaxRange");
}

bool UBTDecorator_EnemyMaxRangeCheck::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
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

	bool Rangeanswer = false;
	float distance = Target->GetDistanceTo(ControllingPawn);
	if (distance< State->getMaxRage()) {
		Rangeanswer = true;
	}
	ABLOG(Warning, TEXT("Distance : %f"), distance);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::AttackRange, Rangeanswer);

	return Rangeanswer;

}


