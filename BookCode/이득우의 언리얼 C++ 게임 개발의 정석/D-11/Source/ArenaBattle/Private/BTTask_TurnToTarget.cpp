// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_TurnToTarget.h"
#include "ABAIController.h"
#include "ABCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ABCharacter = Cast<AABCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ABCharacter)
		return EBTNodeResult::Failed;
	// 현재 폰의 정보를 가져옵니다.

	auto Target = Cast<AABCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AABAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;
	// 타겟의 정보를 가져옵니다.

	FVector LookVector = Target->GetActorLocation() - ABCharacter->GetActorLocation();
	// 바라볼 방향 = 타겟의 위치 - 자신의 위치(벡터)

	LookVector.Z = 0.0f;
	// 높낮이 무시를 위해 Z는 0

	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	// 돌려야할 값 TargetRot을 계산하여 선언합니다.
	ABCharacter->SetActorRotation(FMath::RInterpTo(ABCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));
	// TargetRot만큼 캐릭터를 돌립니다.
	return EBTNodeResult::Succeeded;
}
