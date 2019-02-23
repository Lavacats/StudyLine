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

	Enemy_SEARCH	UMETA(DisplayName = "Enemy_SEARCH"),
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
	bool onBattle = false;
	EnemyCharacterKind EnemyCharacter;

	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EnemyCharacterState curEnemyState;

	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float IdleRange = 0.0f;

	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CurrentChracterSpeed = 0.0f;

	UPROPERTY(Category = STATE, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 IdleNumber = 1;

	EnemyCharacterState preEnemyState;

	int32 enemyCurHp;
	int32 enemyMaxHp;
	int32 enemyATK;

	float invincibleTime = 0.0f;
	bool invincible;
public:	
	// Sets default values for this component's properties
	UEnemyState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	EnemyCharacterKind getEnemyCharacterKind() {return EnemyCharacter;}
	EnemyCharacterState getCurEnemyState() { return curEnemyState; }
	EnemyCharacterState getPreEnemyState() { return preEnemyState; }

	float getIdleRange() { return IdleRange; }
	void setIdleNumber(int32 value) { IdleNumber = value; }
	
};
