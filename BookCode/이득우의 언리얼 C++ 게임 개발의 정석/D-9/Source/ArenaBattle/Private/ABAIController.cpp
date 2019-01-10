// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAIController.h"

const FName AABAIController::HomePosKey(TEXT("HomePos"));
const FName AABAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AABAIController::TargetKey(TEXT("Target"));

AABAIController::AABAIController()
{
	//RepeatInterval = 3.0f;
	//// 3초에 한번씩 길을 찾도록 지정한다
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Book/AI/BB_ABCharacter.BB_ABCharacter"));
	if (BBObject.Succeeded()) {
		BBAsset = BBObject.Object;
		// BBAsset에 레퍼런스 경로를 입력해 BB_ABCharaeter 블랙보드를 불러옵니다.
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObject(TEXT("/Game/Book/AI/BT_ABCharacter.BT_ABCharacter"));
	if (BTObject.Succeeded()) {
		BTAsset = BTObject.Object;
		// BTAsset에 레퍼런스 경로를 입력해 BT_ABCharacter 비헤이비어 트리를 불러옵니다.
	}
}

void AABAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
	// override이므로 부모함수도 실행합니다.
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AABAIController::OnRepeatTimer, RepeatInterval, true);
	//// World의 TimerManager에 반복시간과 반복할 타이머 핸들러, 반복할 함수를 입력합니다
	
	if (UseBlackboard(BBAsset, Blackboard)) {

		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		// 블랙 보드에 HoePosKey의 값을 폰의 현재 위치로 설정합니다.

		if (!RunBehaviorTree(BTAsset)) {
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
			// 블랙보드에 BBAsset을 사용합니다
			// BTAsset 비헤이비어 트리를 실행시킬수 없다면 로그를 띄웁니다.
		}
	}
}

//void AABAIController::UnPossess()
//{
//	Super::UnPossess();
//	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
//	// 빙의가 해제되므로 타이머 매니저에게 Clear를 알립니다.
//}

//void AABAIController::OnRepeatTimer()
//{
//	auto CurrentPawn = GetPawn();
//	ABCHECK(nullptr != CurrentPawn);
//	// CurrentPawn이 있는지 확인합니다.
//
//	UNavigationSystem* NavSystem = UNavigationSystem::GetNavigationSystem(GetWorld());
//	// World에 있는 NavSystem을 가져옵니다.
//
//	if (nullptr == NavSystem)return;
//	// World에 NavSystem이 없다면 함수를 종료합니다.
//
//	FNavLocation NextLocation;
//	// 다음에 찾을 위치 = nexLocation
//	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation)) {
//		UNavigationSystem::SimpleMoveToLocation(this, NextLocation.Location);
//		// 지정된 위치로 이동합니다.
//		ABLOG(Warning, TEXT("NEXT Location : %s"), *NextLocation.Location.ToString());
//	}
//}
