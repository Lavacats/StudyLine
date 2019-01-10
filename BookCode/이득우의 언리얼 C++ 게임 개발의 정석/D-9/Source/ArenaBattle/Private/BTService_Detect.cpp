// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Detect.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	// Node의 이름은 Detect
	Interval = 1.0f;
	// TickNode의 호출주기를 결정하는 변수 현재 값은 1
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	// override

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	// 충돌한 폰을 가져옵니다 (target)
	if (nullptr == ControllingPawn)return;
	// 충돌할 폰이 없다면 함수르 끝냅니다

	UWorld* World = ControllingPawn->GetWorld();
	// World의 정보를 가져옵니다.
	FVector Center = ControllingPawn->GetActorLocation();
	// 현재 폰의 위치 값을 가져옵니다.
	float DetectRadius = 600.0f;
	// 검색할 반지름을 600으로 둡니다.

	if (nullptr == World)return;
	// World가 검새되지않으면 함수를 끝냅니다

	TArray<FOverlapResult> OverlapResults;
	// 정보 목록 관리를 위한 자료구조 TArray

	FCollisionQueryParams CollisionQueryParm(NAME_None, false, ControllingPawn);
	// 충돌 검사를 할 FCollisionQueryParams를 선언합니다.

	bool bResult = World->OverlapMultiByChannel(
		// 반경 내에 있는 모든 캐릭터(NPC포함)를 찾습니다 bool bResult로 반환

		OverlapResults,
		// OverlapResult에 정보를 저장합니다.
		Center,
		// 찾을 값의 중앙값입니다.
		FQuat::Identity,
		// 회전값입니다
		ECollisionChannel::ECC_GameTraceChannel12,
		// 사용할 채녈값
		FCollisionShape::MakeSphere(DetectRadius),
		// Sphere 원형으로 검색합니다.
		CollisionQueryParm
	);

	if(bResult) {
		// 탐색을 했을 때 결과물이 있다면
		for (auto OverlapResult : OverlapResults) {
			// for문을 통해 결과 내역을 찾습니다.
			AABCharacter* ABCharacter = Cast<AABCharacter>(OverlapResult.GetActor());
			// OverlapResult에 있는 Actor를 모두 검색합니다.
			if (ABCharacter && ABCharacter->GetController()->IsPlayerController()) {
				// Actor ABCharacter에 IsPlayerController가 존재한다면
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AABAIController::TargetKey, ABCharacter);
				// BlackBoardd의 Target에 그 액터를 Target오브젝트로 지정합니다.
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				// 탐색범위를 표현하는 DrawDebugSpher를 녹색으로 바꿉니다
				DrawDebugPoint(World, ABCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				// Target 위치를 파란색으로 표시합니다
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), ABCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				// Target과 현재 pawn을 파란색으로 연결합니다.
				return;
			}
		}
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AABAIController::TargetKey, nullptr);
		// Target을 찾지 못했다면 BlackBoarld의 Target에 nullptr의 값을 준다.
	}


	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	// World에 Center기준으로 반지름 DetectRadius를 이용해 붉은색으로 그립니다.
}
