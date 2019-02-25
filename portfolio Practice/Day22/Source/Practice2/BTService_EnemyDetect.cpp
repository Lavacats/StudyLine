// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_EnemyDetect.h"
#include "EnemyAIController.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
#include "EnemyState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_EnemyDetect::UBTService_EnemyDetect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_EnemyDetect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World)return;
	AEnemyCharacter* EnemyCharacter = Cast< AEnemyCharacter>(ControllingPawn);
	if (nullptr == EnemyCharacter)return;
	//auto PlayerCharacter = EnemyCharacter->getPlayerCharacter();
	//if (nullptr == PlayerCharacter)return;
	UEnemyState* EnemyState = EnemyCharacter->getEnemyState();
	if (nullptr == EnemyState)return;

	float distance = FVector::Dist(EnemyCharacter->GetActorLocation(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyAIController::HomePosKey));

	if (EnemyState->getMaxRage() < distance) {
		EnemyState->setEnemyMaxRange(true);
	}
	if (distance < EnemyState->getIdleRange()) {
		EnemyState->setEnemyMaxRange(false);
	}
	ABLOG(Warning, TEXT("Update"));

	bool E_isMaxRange = EnemyState->getEnemyMaxRage();
	bool E_OnBattle = EnemyCharacter->getOnBattle();
	bool E_IsWeapon = EnemyCharacter->getOnWeapon();
	bool E_IsAttackRange = EnemyCharacter->getInAttackRange();

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::MaxRange, E_isMaxRange);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::OnBattle, E_OnBattle);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::IsWeapon, E_IsWeapon);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::AttackRange, E_IsAttackRange);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, EnemyCharacter->getPlayerCharacter());
	if(E_OnBattle && !E_IsWeapon)OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPosKey, EnemyCharacter->getWeapon()->GetActorLocation());


	//===========================================

	/*bool maxAttackRange = EnemyState->getEnemyMaxRage();

	if (EnemyState->getMaxRage() < distance)EnemyState->setEnemyMaxRange(true);
	else EnemyState->setEnemyMaxRange(false);


	bool OnAttack = EnemyCharacter->getOnBattle();
	if (maxAttackRange)OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPosKey, OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyAIController::HomePosKey));

	if (!maxAttackRange)OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::OnBattle, OnAttack);
	else OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::OnBattle, false);

	if (!EnemyState->getEnemyMaxRage()) {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, PlayerCharacter);
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, nullptr);
	}

	bool Weaponvalue = EnemyCharacter->getOnWeapon();

	if (Weaponvalue) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPosKey, PlayerCharacter->GetActorLocation());
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPosKey, EnemyCharacter->getWeapon()->GetActorLocation());
	}*/
}
