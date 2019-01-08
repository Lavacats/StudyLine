// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "ABGameInstance.h"
#include "Components/ActorComponent.h"
#include "ABCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
// 멀티 딜리게이트를 생성합니다.

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
	// 레벨을 지정합니다.
	void SetDamage(float NewDamage);
	// 공격을 받습니다
	void SetHP(float NewHP);
	// 체력이 감소합니다
	float GetAttack();
	// 공격을 합니다
	float GetHPRatio();
	// 최대체력과 현재 체력의 비율을 구합니다.

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
	// Delegate

private:
	struct FABCharacterData* CurrentStatData = nullptr;
	// 캐릭터 정보를 관리할 변수

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;
	// 현재 레벨

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;
	// 현재 체력
	// Transient
	// 언리얼 오브젝트는 직렬화 기능이 있어서
	// UPROPERY 속성을 저장하고 로딩할 수 있다.
	// CUrrentHP는 매번 값이 변하므로 저장하기 번거롭고 자리를 차지한다
	// Transient를 사용해 직렬화에서 제외시킨다.
	
};
