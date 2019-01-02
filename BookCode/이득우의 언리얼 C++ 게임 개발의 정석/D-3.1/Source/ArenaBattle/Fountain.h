// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "ArenaBattle.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class ARENABATTLE_API AFountain : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;
	// virtual�� ���� �� 3���� �Լ��� ��ӹ޾Ҵٴ� ����� �� �� ������
	// override�� ���� 3���� �Լ��� ��ӹ��� �Լ��� ������ �߰��Ѵٴ� ���� �� �� �ִ�.
	// ������ ȣ����� PostInitializeComponents()->BeginPlay()-> ���� ���� -> EndPlay();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	// UPROPERTY : �𸮾� ���� ȯ�濡�� �𸮾� ������ �ڵ����� ��ü�� �����ϴ� ����
	// VisibleAnywhere : ��ü�� �����Ϳ��� �� �� �ֵ��� �Ѵ�.
	UStaticMeshComponent *Body;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Water;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent *Light;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *Splash;

	UPROPERTY(EditAnywhere, Category=ID)
	// EditAnywhere : �𸮾� �����Ϳ��� �Ӽ��� �����͸� �����ϵ��� �Ѵ�.
	// Category=�з��� : ������ �з������� �з��Ѵ�.
	int32 ID;

	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* Movement;

private:
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float RotateSpeed;
	// ȸ����
	// 1. �𸮾� �����Ϳ��� ������ �����ϵ��� UPROPERTY���� EditAnywhereŰ���带 ����մϴ�
	// 2. ī�װ� �з��� Stat�� �з��մϴ�
	// 3. ������ �����ϱ� ���� private������ ����մϴ�
	// private������ ����� ��� ���� �������� ���� �����Ϳ��� ������ �� �����Ƿ� EditAnywhere�� ����˴ϴ�.
	// �����͸� ������ �� �ִ� ���ÿ� �����Ϳ����� ������ �� �ִ� Ű���� META�� �߰��մϴ�
	// Meta = (AllowPrivateAccess = true)�� ���� �����Ͱ� ���еǴ� ���ÿ� �����Ϳ����� �����Ҽ� �ְԵǾ����ϴ�.(ĸ��ȭ)
};
