// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindPatrolPos.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
	// NodeName을 FindPatrolPos로 짓습니다.
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	// override

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	// World에서 Pawn을 가져옵니다.

	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;
	// Pawn이 없다면 Failed를 반환합니다.

	UNavigationSystem* NavSystem = UNavigationSystem::GetNavigationSystem(ControllingPawn->GetWorld());
	// Pawn을 통해 World에서 NavigationSystem을 가져옵니다.
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;
	// NavaSystem이 없다면 Failed를 반환합니다.

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AABAIController::HomePosKey);
	// Origin 벡터 값에 HomePoskey값을 가져옵니다.

	FNavLocation NextPatrol;
	// 다음 위치를 가리킬 NavLocationd을 선언합니다.

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextPatrol))
		// NavSysstem에 0부터 500사이의 무작위 벡터를 다음 목적지로 선언합니다.
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AABAIController::PatrolPosKey, NextPatrol.Location);
		// NextPatrol의 값을 BlckboardComponent에 적용합니다
		return EBTNodeResult::Succeeded;
		// 적용하는데 성공했다면 Succeded를 반환하니다
	}
	return EBTNodeResult::Failed;
	// NavSystem이 없거나 오류가 난 경우 Failed를 반환합니다.

}
