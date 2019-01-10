// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "ABCharacter.h"
#include "ABItemBox.h"
#include "GameFramework/Actor.h"
#include "ABSection.generated.h"

UCLASS()
class ARENABATTLE_API AABSection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABSection();
	virtual void OnConstruction(const FTransform& Transform)override;
	// 액터와 에디터가 연동되는 함수
	// 에디터 작업에서 선택한 액터의 속성이나 트랜ㅅ폼 정보가 변결될때 이 함수가 실행된다.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	enum class ESectionState : uint8
	{
		READY=0,
		BATTLE,
		COMPLETE
	};
	// 트리거 상태
	// READY: 준비 상태 문이 열려있고 플레이어가 존재하지않는 상태
	// BATTLE: 문이 닫히며 이정시간이 지나면 NPC와 아이템상자가 생성된다.
	// COMPLERE: 닫힌 문이 열리며, 문마다 배치한 트리거 게이트로 플레이어가 감지된다.(다음스테이지이동)
	
	void SetState(ESectionState NewState);
	// 문의 상태를 조절합니다.

	ESectionState CurrentState = ESectionState::READY;
	// 현재 상태를 나타냅니다.

	void OperateGates(bool bOpen = true);
	// 문이 열리고 닫히는걸 조절하는 함수

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedCmponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult);
	// 플레이어가 방에 있는지 검사하는 함수

	UFUNCTION()
	void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool BFromSweep, const FHitResult &SweepResult);
	// 플레이어가 게이트에 닿았는지 검사하는 함수

	void OnNPCSpawn();
	// NPC를 소환시키는 시스템

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;
	//배경으로 사용할 스태틱메시 컴포넌트

	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TArray<UStaticMeshComponent*> GateMeshes;
	// 게이트 입구에 사용할 스태틱 메시

	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
	TArray<UBoxComponent*> GateTriggers;
	// 게이트의 충돌을 담당할 BoxComponent(플레이어만 캄지)

	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
	UBoxComponent* Trigger;
	// 그냥 Trigger

	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
	bool bNoBattle;
	// 플레이어가 들어와서 배틀모드가 되었는지 체크합니다.(NPC가 공격합니다)

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float EnemySpawnTime;
	// 적(NPC)의 스폰시간

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float ItemBoxSpawnTime;
	// 아이템박스의 스폰시간

	FTimerHandle SpawnNPCTimerHandle = {};
	// NPC를 조종할 핸들러
	FTimerHandle SpawnItemBoxTimerHandle = {};
	// ITem박스를 조종할 핸들러
};
