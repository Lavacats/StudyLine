// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ArenaBattle.h"
#include "AIController.h"
#include "ABAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AABAIController();
	virtual void Possess(APawn* InPawn) override;
	// Pawn�� ���� �ϴ� �Լ� override
	//virtual void UnPossess() override;
	// Pawn�� ���Ǹ� �����ϴ� �Լ� Override

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	// Ű�� �̸��� ���� �ٲ��� �ʴ� �ٴ� ���� �Ͽ� static const�� ����߽��ϴ�

	void RunAI();
	void StopAI();

private:
	//void OnRepeatTimer();
	//// �ֱ������� �ݺ��� �Լ�
	//FTimerHandle RepeatTimerHandle;
	//// �𸮾� �������� �ð��� ��� TimerHandle
	//float RepeatInterval;
	// �� �ʸ��� �ѹ��� ��ã�⸦ ���� �ð�����
	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;
};
