// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "Components/ActorComponent.h"
#include "EnemyState.generated.h"

UENUM()
enum class EnemyCharacterKind : uint8 {
	Character_Bokoblin	UMETA(DisplayName = "Character_Bokoblin"),
	Character_Skeleton	UMETA(DisplayName = "Character_Skeleton")
};

UENUM()
enum class EnemyCharacterState : uint8 {
	Enemy_IDLE		UMETA(DisplayName = "Enemy_IDLE"),
	Enemy_RUN		UMETA(DisplayName = "Enemy_RUN"),
	Enemy_ATTACK	UMETA(DisplayName = "Enemy_ATTACK"),
	Enemy_HURT		UMETA(DisplayName = "Enemy_HURT"),
	Enemy_DEATH		UMETA(DisplayName = "Enemy_DEATH")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICE2_API UEnemyState : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EnemyCharacterKind EnemyCharacter;
	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EnemyCharacterState curEnemyState;
	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float IdleRange = 0.0f;
	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackRange = 0.0f;
	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxAttackRange = 0.0f;
	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CurrentChracterSpeed = 0.0f;
	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 IdleNumber = 1;
	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool OnBattle;

	bool EnemyMaxRange;
	bool InAttackRange;
	bool hasWeapon;

	bool AttackDelay;
	float AttackDelayTimer;
	FTimerHandle AttackDelayTimerHandler;


	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 enemyCurHp;
	int32 enemyMaxHp;
	int32 enemyATK;

public:	
	// Sets default values for this component's properties
	UEnemyState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void HurtEnemy();
	void AttackDelayFuncition();
	void DelayTimer();

	EnemyCharacterKind getEnemyCharacterKind() {return EnemyCharacter;}
	EnemyCharacterState getCurEnemyState() { return curEnemyState; }

	float getEnemyAttackRange() { return AttackRange; }
	float getIdleRange() { return IdleRange; }
	float getMaxRage() {return MaxAttackRange;}
	bool getEnemyMaxRage() { return EnemyMaxRange; }
	bool getOnBattle() { return OnBattle; }
	bool getHasWeapon() { return hasWeapon; }
	bool getInAttackRange() { return InAttackRange; }

	void setEnemyMaxRange(bool value) { EnemyMaxRange = value; }
	void setIdleNumber(int32 value) { IdleNumber = value; }
	void setOnBattle(bool value) { OnBattle = value; }
	void setHasWeapon(bool value) { hasWeapon = value; }
	void setInAttackRange(bool value) { InAttackRange = value; }
	void setCurEnemyState(EnemyCharacterState value) { curEnemyState= value; }
};
