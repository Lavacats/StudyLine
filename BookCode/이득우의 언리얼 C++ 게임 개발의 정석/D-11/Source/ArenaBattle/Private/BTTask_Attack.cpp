// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "ABAIController.h"
#include "ABCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	// FinishedLatenTask와 같이 태스크의 진행을 알아야 하기 때메 tick을 활성화한다.
	IsAttacking = false;
	// 시작 공격 불값을 false로 준다.
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ABCharacter = Cast<AABCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	// AI에서 폰을 가져옵니다.
	if (nullptr == ABCharacter)
		return EBTNodeResult::Failed;
	// Pawn이 없다면 함수를 끝냅니다.

	ABCharacter->Attack();
	// 이번 Task에서 캐릭터가 공격을 합니다.
	IsAttacking = true;
	// 공격 불값으로 true를 줍니다.
	ABCharacter->OnAttackEnd.AddLambda([this]()->void {
		IsAttacking = false;
		// 공격이 끝날때 IsAttacking이 false가 되도록합니다.
	});

	return EBTNodeResult::InProgress;
	// 공격 애니메이션이 끝날 때까지 대기해야하는 지연 태스크이다.
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);
	if (!IsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		// 공격 불값이 false라면 task를 끝냅니다.
	}
	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	// 태스크가 끝났음을 알려주는게 FinishLatenTask이다.
}
