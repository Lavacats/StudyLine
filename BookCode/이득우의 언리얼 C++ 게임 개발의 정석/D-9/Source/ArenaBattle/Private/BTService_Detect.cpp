// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Detect.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	// Node�� �̸��� Detect
	Interval = 1.0f;
	// TickNode�� ȣ���ֱ⸦ �����ϴ� ���� ���� ���� 1
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	// override

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	// �浹�� ���� �����ɴϴ� (target)
	if (nullptr == ControllingPawn)return;
	// �浹�� ���� ���ٸ� �Լ��� �����ϴ�

	UWorld* World = ControllingPawn->GetWorld();
	// World�� ������ �����ɴϴ�.
	FVector Center = ControllingPawn->GetActorLocation();
	// ���� ���� ��ġ ���� �����ɴϴ�.
	float DetectRadius = 600.0f;
	// �˻��� �������� 600���� �Ӵϴ�.

	if (nullptr == World)return;
	// World�� �˻����������� �Լ��� �����ϴ�

	TArray<FOverlapResult> OverlapResults;
	// ���� ��� ������ ���� �ڷᱸ�� TArray

	FCollisionQueryParams CollisionQueryParm(NAME_None, false, ControllingPawn);
	// �浹 �˻縦 �� FCollisionQueryParams�� �����մϴ�.

	bool bResult = World->OverlapMultiByChannel(
		// �ݰ� ���� �ִ� ��� ĳ����(NPC����)�� ã���ϴ� bool bResult�� ��ȯ

		OverlapResults,
		// OverlapResult�� ������ �����մϴ�.
		Center,
		// ã�� ���� �߾Ӱ��Դϴ�.
		FQuat::Identity,
		// ȸ�����Դϴ�
		ECollisionChannel::ECC_GameTraceChannel12,
		// ����� ä�㰪
		FCollisionShape::MakeSphere(DetectRadius),
		// Sphere �������� �˻��մϴ�.
		CollisionQueryParm
	);

	if(bResult) {
		// Ž���� ���� �� ������� �ִٸ�
		for (auto OverlapResult : OverlapResults) {
			// for���� ���� ��� ������ ã���ϴ�.
			AABCharacter* ABCharacter = Cast<AABCharacter>(OverlapResult.GetActor());
			// OverlapResult�� �ִ� Actor�� ��� �˻��մϴ�.
			if (ABCharacter && ABCharacter->GetController()->IsPlayerController()) {
				// Actor ABCharacter�� IsPlayerController�� �����Ѵٸ�
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AABAIController::TargetKey, ABCharacter);
				// BlackBoardd�� Target�� �� ���͸� Target������Ʈ�� �����մϴ�.
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				// Ž�������� ǥ���ϴ� DrawDebugSpher�� ������� �ٲߴϴ�
				DrawDebugPoint(World, ABCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				// Target ��ġ�� �Ķ������� ǥ���մϴ�
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), ABCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				// Target�� ���� pawn�� �Ķ������� �����մϴ�.
				return;
			}
		}
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AABAIController::TargetKey, nullptr);
		// Target�� ã�� ���ߴٸ� BlackBoarld�� Target�� nullptr�� ���� �ش�.
	}


	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	// World�� Center�������� ������ DetectRadius�� �̿��� ���������� �׸��ϴ�.
}
