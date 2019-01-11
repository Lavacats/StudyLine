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
	// Pawn에 빙의 하는 함수 override
	//virtual void UnPossess() override;
	// Pawn에 빙의를 해제하는 함수 Override

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	// 키의 이름을 절때 바꾸지 않는 다는 가정 하에 static const를 사용했습니다

	void RunAI();
	void StopAI();

private:
	//void OnRepeatTimer();
	//// 주기적으로 반복할 함수
	//FTimerHandle RepeatTimerHandle;
	//// 언리얼 엔진에서 시간을 재는 TimerHandle
	//float RepeatInterval;
	// 몇 초마다 한번씩 길찾기를 할지 시간기준
	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;
};
