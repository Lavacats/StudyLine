// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "EnemyState.h"
#include "Weapon_Sword.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;
UCLASS()
class PRACTICE2_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Enemy, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* EnemyMesh;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UEnemyState* EnemyState;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxSpeed;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPawnSensingComponent* pawnSensing; 
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool OnBattle;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HPBarWidget;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FTimerHandle AttackTimerHandle;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackTimer;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool hasWeapon;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AWeapon_Sword* WeaponLocation;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool InAttackRange;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	APawn* PlayerCharacterPawn;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		AWeapon_Sword* EquapWeapon;
public:
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void BattleToIdle();
	UFUNCTION()
	void getWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	void setEnemyState(UEnemyState* state) { EnemyState = state; }
	
	UEnemyState* getEnemyState() { return EnemyState; }
	APawn* getPlayerCharacter() { return PlayerCharacterPawn; }
	bool getOnBattle() { return OnBattle; }
	bool getOnWeapon() { return hasWeapon; }
	bool getInAttackRange() { return InAttackRange; }
	void setInAttackRange(bool value) { InAttackRange = value; }
	FVector getWeaponLocation();
	AActor* getWeapon() { return WeaponLocation; }
};
