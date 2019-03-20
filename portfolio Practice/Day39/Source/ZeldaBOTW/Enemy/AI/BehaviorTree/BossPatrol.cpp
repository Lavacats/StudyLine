// Fill out your copyright notice in the Description page of Project Settings.

#include "BossPatrol.h"
#include "Player/PlayerCharacter.h"
#include "Enemy/BossCharacter.h"
#include "Enemy/AI/BossAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBossPatrol::UBossPatrol()
{
	NodeName = TEXT("Patrol");
	Interval = 1.0f;
}

void UBossPatrol::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World)return;
	ABossCharacter* BossCharacter = Cast< ABossCharacter>(ControllingPawn);
	if (nullptr == BossCharacter)return;
	UNavigationSystem* NavSystem = UNavigationSystem::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem) return;
	
	FVector Homeposkey = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ABossAIController::HomePos);
	FNavLocation NextPatrol;
	float xasd = 0;
	xasd = BossCharacter->getPatrolRange();
	//ABLOG(Warning, TEXT("%f"), xasd);
	if (NavSystem->GetRandomPointInNavigableRadius(Homeposkey, BossCharacter->getPatrolRange(), NextPatrol)) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ABossAIController::NextPos, NextPatrol.Location);
	}
	//float distanceToHome = FVector::Dist(BossCharacter->GetActorLocation(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyAIController::HomePosKey));
	//if (EnemyState->getMaxRage() < distanceToHome) {
	//	EnemyState->setEnemyMaxRange(true);
	//	EnemyState->setOnBattle(false);
	//}
	//if (distanceToHome < EnemyState->getIdleRange()) {
	//	EnemyState->setEnemyMaxRange(false);
	//}

	//float distanceToPlayer = ControllingPawn->GetDistanceTo(BossCharacter->getPlayerCharacter());
	//if (distanceToPlayer < EnemyState->getEnemyAttackRange()) {
	//	EnemyState->setInAttackRange(true);
	//}
	//else {
	//	EnemyState->setInAttackRange(false);
	//}

	//bool E_OnBattle = EnemyState->getOnBattle();
	//bool E_IsWeapon = EnemyState->getHasWeapon();
	//bool E_isMaxRange = EnemyState->getEnemyMaxRage();
	//bool E_IsAttackRange = EnemyState->getInAttackRange();

	//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABossAIController::MaxRange, E_isMaxRange);
	//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABossAIController::OnBattle, E_OnBattle);
	//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABossAIController::IsWeapon, E_IsWeapon);
	//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABossAIController::AttackRange, E_IsAttackRange);

	//OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABossAIController::TargetKey, BossCharacter->getPlayerCharacter());
	//if (E_OnBattle && !E_IsWeapon)OwnerComp.GetBlackboardComponent()->SetValueAsVector(ABossAIController::PatrolPosKey, BossCharacter->getWeapon()->GetActorLocation());

}
