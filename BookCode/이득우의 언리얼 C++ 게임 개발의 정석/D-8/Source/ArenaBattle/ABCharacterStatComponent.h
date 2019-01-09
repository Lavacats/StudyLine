// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "ABGameInstance.h"
#include "Components/ActorComponent.h"
#include "ABCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
// ��Ƽ ��������Ʈ�� �����մϴ�.

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENABATTLE_API UABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetNewLevel(int32 NewLevel);
	// ������ �����մϴ�.
	void SetDamage(float NewDamage);
	// ������ �޽��ϴ�
	void SetHP(float NewHP);
	// ü���� �����մϴ�
	float GetAttack();
	// ������ �մϴ�
	float GetHPRatio();
	// �ִ�ü�°� ���� ü���� ������ ���մϴ�.

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
	// Delegate

private:
	struct FABCharacterData* CurrentStatData = nullptr;
	// ĳ���� ������ ������ ����

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;
	// ���� ����

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;
	// ���� ü��
	// Transient
	// �𸮾� ������Ʈ�� ����ȭ ����� �־
	// UPROPERY �Ӽ��� �����ϰ� �ε��� �� �ִ�.
	// CUrrentHP�� �Ź� ���� ���ϹǷ� �����ϱ� ���ŷӰ� �ڸ��� �����Ѵ�
	// Transient�� ����� ����ȭ���� ���ܽ�Ų��.
	
};
