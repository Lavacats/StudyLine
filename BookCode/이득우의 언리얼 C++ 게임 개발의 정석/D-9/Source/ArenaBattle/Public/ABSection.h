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
	// ���Ϳ� �����Ͱ� �����Ǵ� �Լ�
	// ������ �۾����� ������ ������ �Ӽ��̳� Ʈ������ ������ ����ɶ� �� �Լ��� ����ȴ�.

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
	// Ʈ���� ����
	// READY: �غ� ���� ���� �����ְ� �÷��̾ ���������ʴ� ����
	// BATTLE: ���� ������ �����ð��� ������ NPC�� �����ۻ��ڰ� �����ȴ�.
	// COMPLERE: ���� ���� ������, ������ ��ġ�� Ʈ���� ����Ʈ�� �÷��̾ �����ȴ�.(�������������̵�)
	
	void SetState(ESectionState NewState);
	// ���� ���¸� �����մϴ�.

	ESectionState CurrentState = ESectionState::READY;
	// ���� ���¸� ��Ÿ���ϴ�.

	void OperateGates(bool bOpen = true);
	// ���� ������ �����°� �����ϴ� �Լ�

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedCmponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult);
	// �÷��̾ �濡 �ִ��� �˻��ϴ� �Լ�

	UFUNCTION()
	void OnGateTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool BFromSweep, const FHitResult &SweepResult);
	// �÷��̾ ����Ʈ�� ��Ҵ��� �˻��ϴ� �Լ�

	void OnNPCSpawn();
	// NPC�� ��ȯ��Ű�� �ý���

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;
	//������� ����� ����ƽ�޽� ������Ʈ

	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	TArray<UStaticMeshComponent*> GateMeshes;
	// ����Ʈ �Ա��� ����� ����ƽ �޽�

	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
	TArray<UBoxComponent*> GateTriggers;
	// ����Ʈ�� �浹�� ����� BoxComponent(�÷��̾ į��)

	UPROPERTY(VisibleAnywhere, Category = Trigger, Meta = (AllowPrivateAccess = true))
	UBoxComponent* Trigger;
	// �׳� Trigger

	UPROPERTY(EditAnywhere, Category = State, Meta = (AllowPrivateAccess = true))
	bool bNoBattle;
	// �÷��̾ ���ͼ� ��Ʋ��尡 �Ǿ����� üũ�մϴ�.(NPC�� �����մϴ�)

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float EnemySpawnTime;
	// ��(NPC)�� �����ð�

	UPROPERTY(EditAnywhere, Category = Spawn, Meta = (AllowPrivateAccess = true))
	float ItemBoxSpawnTime;
	// �����۹ڽ��� �����ð�

	FTimerHandle SpawnNPCTimerHandle = {};
	// NPC�� ������ �ڵ鷯
	FTimerHandle SpawnItemBoxTimerHandle = {};
	// ITem�ڽ��� ������ �ڵ鷯
};
