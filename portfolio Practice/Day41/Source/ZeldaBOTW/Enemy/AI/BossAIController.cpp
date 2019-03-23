// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAIController.h"
#include "Enemy/BossCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ABossAIController::HomePos(TEXT("HomePos"));
const FName ABossAIController::NextPos(TEXT("NextPos"));
const FName ABossAIController::Target(TEXT("Target"));
const FName ABossAIController::OnPatrol(TEXT("OnPatrol"));
const FName ABossAIController::OnBattle(TEXT("OnBattle"));
const FName ABossAIController::PatrolRange(TEXT("PatrolRange"));
const FName ABossAIController::FindRange(TEXT("FindRange"));
const FName ABossAIController::AttackRange(TEXT("AttackRange"));
// 이름이 절때 변하지 않는다는 가정 하에 satic const 를 사용한 변수 초기 값

ABossAIController::ABossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/EnemyCharacter/GuardianBoss/BehaviorTree/BossBlackTree.BossBlackTree"));
	if (BBObject.Succeeded()) {
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/EnemyCharacter/GuardianBoss/BehaviorTree/BossBehaviorTree.BossBehaviorTree"));
	if (BTObject.Succeeded()) {
		BTAsset = BTObject.Object;
	}
}

void ABossAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
	if (UseBlackboard(BBAsset, Blackboard)) {
		ABossCharacter* BossCharacter = Cast< ABossCharacter>(InPawn);
		float Vx = 0.0f;
		float Vy = 0.0f;
		float Vz = 0.0f;
		Vx = BossCharacter->getTreasureLotation().X;
		Vy = BossCharacter->getTreasureLotation().Y;
		Vz = BossCharacter->getTreasureLotation().Z;
		Blackboard->SetValueAsVector(HomePos, FVector(Vx,Vy,Vz));
	
		if (!RunBehaviorTree(BTAsset)) {
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}




