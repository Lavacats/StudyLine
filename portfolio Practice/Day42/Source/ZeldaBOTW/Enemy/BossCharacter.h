// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "Enemy/BossUIClass.h"
#include "Enemy/EnemyCharacter.h"
#include "GameFramework/Character.h"
#include "BossCharacter.generated.h"

UCLASS()
class ZELDABOTW_API ABossCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = Boss, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BossHeadMesh;
	UPROPERTY(Category = Boss, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AActor* Treasure;
	UPROPERTY(Category = Boss, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UBossUIClass> HDWidgetClass;
	UPROPERTY(Category = Boss, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBossUIClass* BossUI;
	UPROPERTY(Category = Boss, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UEnemyCharacterState* BossState;
	float patrolRange;
	float FIndRange;
	float AttackRange;
	bool OnBattle;
public:
	// Sets default values for this character's properties
	ABossCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector getTreasureLotation();
	USkeletalMeshComponent* getBossHeadMesh() { return BossHeadMesh; }
	float getPatrolRange();
	float getFIndRange();
	float getAttackRange();
	void setBossHPUI(bool value);

	void HurtBoss();

	bool getOnBattle() { return OnBattle; }
	void setOnBattle(bool value) { OnBattle = value; }
};
