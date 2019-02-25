// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_EnemyHasWeapon.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_EnemyHasWeapon::UBTDecorator_EnemyHasWeapon()
{
	NodeName = TEXT("EnemyHasWeapon");
}

bool UBTDecorator_EnemyHasWeapon::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto EnemyCharacter = Cast<AEnemyCharacter>(ControllingPawn);
	if (nullptr == EnemyCharacter)
		return false;


	return EnemyCharacter->getOnWeapon();
}
