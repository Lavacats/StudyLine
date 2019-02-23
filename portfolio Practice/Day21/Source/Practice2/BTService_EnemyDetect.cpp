// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_EnemyDetect.h"
#include "EnemyAIController.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.h"
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

	/*APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;
	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0f;
	if (nullptr == World)return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	if (bResult) {
		for (auto OverlapResult : OverlapResults) {
			APlayerCharacter* PlayerCharacter = Cast< APlayerCharacter>(OverlapResult.GetActor());
			if (PlayerCharacter && PlayerCharacter->GetController()->IsPlayerController()) {
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, PlayerCharacter);
				
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, PlayerCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), PlayerCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
			else {
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, nullptr);
			}
		}
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, nullptr);
	}*/
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World)return;

	AEnemyCharacter* EnemyCharacter = Cast< AEnemyCharacter>(ControllingPawn);
	if (nullptr == EnemyCharacter)return;

	bool Battlevalue = EnemyCharacter->getOnBattle();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::OnBattle, Battlevalue);
	
	auto PlayerCharacter = EnemyCharacter->getPlayerCharacter();
	if (nullptr == PlayerCharacter)return;

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, PlayerCharacter);

	bool Weaponvalue = EnemyCharacter->getOnWeapon();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::IsWeapon, Weaponvalue);
	
	if (Weaponvalue) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPosKey, PlayerCharacter->GetActorLocation());
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPosKey, EnemyCharacter->getWeapon()->GetActorLocation());
	}

	bool AttackRange = EnemyCharacter->getInAttackRange();
	//if(AttackRange)OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::PatrolPosKey,nullptr);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyAIController::AttackRange, AttackRange);
}
