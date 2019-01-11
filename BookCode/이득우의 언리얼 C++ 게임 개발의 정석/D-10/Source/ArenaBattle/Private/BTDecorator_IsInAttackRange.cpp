// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_IsInAttackRange.h"
#include "ABAIController.h"
#include "ABCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
	// NodeNaem 을 CanAttack으로 둔다.
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	// Pawn의 정보를 AI에서 가져온다.

	if (nullptr == ControllingPawn)
		return false;
	// 폰이 없을 경우 함수를 끝낸다

	auto Target = Cast<AABCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AABAIController::TargetKey));
	// BlackBoard에서 Target의 정보를 가져온다.
	if (nullptr == Target)
		return false;
	// Target이 없을 경우 함수를 끝낸다.

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	// Target과의 거리가 200아래이면 참을 아니면 거짓을 bResult에 담는다.
	return bResult;
}
