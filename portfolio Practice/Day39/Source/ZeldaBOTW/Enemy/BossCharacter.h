// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "GameFramework/Character.h"
#include "BossCharacter.generated.h"

UCLASS()
class ZELDABOTW_API ABossCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = Enemy, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BossMesh;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AActor* Treasure;

	float patrolRange;
	float FIndRange;
	float AttackRange;
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
	float getPatrolRange();
	float getFIndRange();
	float getAttackRange();
};
