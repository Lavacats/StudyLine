// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindPatrolPos.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
	// NodeName�� FindPatrolPos�� �����ϴ�.
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	// override

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	// World���� Pawn�� �����ɴϴ�.

	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;
	// Pawn�� ���ٸ� Failed�� ��ȯ�մϴ�.

	UNavigationSystem* NavSystem = UNavigationSystem::GetNavigationSystem(ControllingPawn->GetWorld());
	// Pawn�� ���� World���� NavigationSystem�� �����ɴϴ�.
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;
	// NavaSystem�� ���ٸ� Failed�� ��ȯ�մϴ�.

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AABAIController::HomePosKey);
	// Origin ���� ���� HomePoskey���� �����ɴϴ�.

	FNavLocation NextPatrol;
	// ���� ��ġ�� ����ų NavLocationd�� �����մϴ�.

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextPatrol))
		// NavSysstem�� 0���� 500������ ������ ���͸� ���� �������� �����մϴ�.
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AABAIController::PatrolPosKey, NextPatrol.Location);
		// NextPatrol�� ���� BlckboardComponent�� �����մϴ�
		return EBTNodeResult::Succeeded;
		// �����ϴµ� �����ߴٸ� Succeded�� ��ȯ�ϴϴ�
	}
	return EBTNodeResult::Failed;
	// NavSystem�� ���ų� ������ �� ��� Failed�� ��ȯ�մϴ�.

}
