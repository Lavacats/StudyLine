// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerCharacterState.h"
#include "Player/PlayerTrace.h"
#include "Player/PlayerWeapon.h"
#include "Weapon/Weapon_Arrow.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterBattleController.generated.h"

UCLASS()
class ZELDABOTW_API APlayerCharacterBattleController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* p2PlayerCharacter;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPlayerCharacterState* p2PlayerSate;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	APlayerWeapon* PlayerWeapon;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPlayerTrace* PlayerTrace;
private:
	bool IsBattle;
	bool IsShoot;
	bool CanShootArrow;
	bool IsSword;

	int32 WeaponIdleTime = 0;
	FTimerHandle AttackTimerHandle;
public:
	APlayerCharacterBattleController();

	virtual void BeginPlay() override;
	void PlayerBattleSetting(APlayerCharacter* Character, UPlayerCharacterState* Sate, UPlayerTrace* Trace);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void PlayerShotStart();
	void PlayerShotEnd();
	void PlayerAttackStart();

	void PlayerHurt();

	void ShootArrow();
	void WeaponToIdleTimer();
	void WeaponToIdle();

	void WeaponChangeIDLE();
	void WeaponChangeSword();
	void WeaponChangeBow();

	void CounterAttackEnemy();

	void PlayerWeaponChangeLeft();
	void PlayerWeaponChangeRight();

	bool getIsSword() { return IsSword; }
	bool getIsShoot() { return IsShoot; }
	bool getIsBattle() { return IsBattle; }
	bool getCanShootArrow() { return CanShootArrow; }

	void setIsSword(bool value) { IsSword = value; }
	void setIsShoot(bool value) { IsShoot = value; }
	void setCanShootArrow(bool value) { CanShootArrow = value; }
	void setPlayerWeapon(APlayerWeapon* Weapon) { PlayerWeapon = Weapon; }
};
