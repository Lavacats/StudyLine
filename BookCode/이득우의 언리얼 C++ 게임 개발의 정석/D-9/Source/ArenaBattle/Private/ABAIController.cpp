// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAIController.h"

const FName AABAIController::HomePosKey(TEXT("HomePos"));
const FName AABAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AABAIController::TargetKey(TEXT("Target"));

AABAIController::AABAIController()
{
	//RepeatInterval = 3.0f;
	//// 3�ʿ� �ѹ��� ���� ã���� �����Ѵ�
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Book/AI/BB_ABCharacter.BB_ABCharacter"));
	if (BBObject.Succeeded()) {
		BBAsset = BBObject.Object;
		// BBAsset�� ���۷��� ��θ� �Է��� BB_ABCharaeter �����带 �ҷ��ɴϴ�.
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObject(TEXT("/Game/Book/AI/BT_ABCharacter.BT_ABCharacter"));
	if (BTObject.Succeeded()) {
		BTAsset = BTObject.Object;
		// BTAsset�� ���۷��� ��θ� �Է��� BT_ABCharacter �����̺�� Ʈ���� �ҷ��ɴϴ�.
	}
}

void AABAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
	// override�̹Ƿ� �θ��Լ��� �����մϴ�.
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AABAIController::OnRepeatTimer, RepeatInterval, true);
	//// World�� TimerManager�� �ݺ��ð��� �ݺ��� Ÿ�̸� �ڵ鷯, �ݺ��� �Լ��� �Է��մϴ�
	
	if (UseBlackboard(BBAsset, Blackboard)) {

		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		// �� ���忡 HoePosKey�� ���� ���� ���� ��ġ�� �����մϴ�.

		if (!RunBehaviorTree(BTAsset)) {
			ABLOG(Error, TEXT("AIController couldn't run behavior tree!"));
			// �����忡 BBAsset�� ����մϴ�
			// BTAsset �����̺�� Ʈ���� �����ų�� ���ٸ� �α׸� ���ϴ�.
		}
	}
}

//void AABAIController::UnPossess()
//{
//	Super::UnPossess();
//	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
//	// ���ǰ� �����ǹǷ� Ÿ�̸� �Ŵ������� Clear�� �˸��ϴ�.
//}

//void AABAIController::OnRepeatTimer()
//{
//	auto CurrentPawn = GetPawn();
//	ABCHECK(nullptr != CurrentPawn);
//	// CurrentPawn�� �ִ��� Ȯ���մϴ�.
//
//	UNavigationSystem* NavSystem = UNavigationSystem::GetNavigationSystem(GetWorld());
//	// World�� �ִ� NavSystem�� �����ɴϴ�.
//
//	if (nullptr == NavSystem)return;
//	// World�� NavSystem�� ���ٸ� �Լ��� �����մϴ�.
//
//	FNavLocation NextLocation;
//	// ������ ã�� ��ġ = nexLocation
//	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation)) {
//		UNavigationSystem::SimpleMoveToLocation(this, NextLocation.Location);
//		// ������ ��ġ�� �̵��մϴ�.
//		ABLOG(Warning, TEXT("NEXT Location : %s"), *NextLocation.Location.ToString());
//	}
//}
