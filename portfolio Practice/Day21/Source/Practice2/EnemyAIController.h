// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	static const FName OnBattle;
	static const FName IsWeapon;
	static const FName AttackRange;

private:
	UPROPERTY()
		class UBehaviorTree*  BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;

public:
	AEnemyAIController();
	virtual void Possess(APawn* InPawn) override;





};
