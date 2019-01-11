// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "ABAIController.h"
#include "ABCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	// FinishedLatenTask�� ���� �½�ũ�� ������ �˾ƾ� �ϱ� ���� tick�� Ȱ��ȭ�Ѵ�.
	IsAttacking = false;
	// ���� ���� �Ұ��� false�� �ش�.
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ABCharacter = Cast<AABCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	// AI���� ���� �����ɴϴ�.
	if (nullptr == ABCharacter)
		return EBTNodeResult::Failed;
	// Pawn�� ���ٸ� �Լ��� �����ϴ�.

	ABCharacter->Attack();
	// �̹� Task���� ĳ���Ͱ� ������ �մϴ�.
	IsAttacking = true;
	// ���� �Ұ����� true�� �ݴϴ�.
	ABCharacter->OnAttackEnd.AddLambda([this]()->void {
		IsAttacking = false;
		// ������ ������ IsAttacking�� false�� �ǵ����մϴ�.
	});

	return EBTNodeResult::InProgress;
	// ���� �ִϸ��̼��� ���� ������ ����ؾ��ϴ� ���� �½�ũ�̴�.
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);
	if (!IsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		// ���� �Ұ��� false��� task�� �����ϴ�.
	}
	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	// �½�ũ�� �������� �˷��ִ°� FinishLatenTask�̴�.
}
