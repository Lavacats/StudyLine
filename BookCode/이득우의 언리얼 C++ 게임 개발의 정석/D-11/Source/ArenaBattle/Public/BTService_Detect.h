// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"
/**
 * 
 */
UCLASS()
class ARENABATTLE_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_Detect();
	// 서비스는 독립적으로 동작하지 않고, 컴포짓 노드에 부착되는 노드입니다
	// 이번에는 플레이어를 탐지, 이동, 대기하는 셀렉터 컴포짓에 추가하여 매번 실행되도록 합니다.

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
	// TickNode는 컴포짓 노드가 활성화될 경우 주기적으로 호출되는 함수다

	
};
