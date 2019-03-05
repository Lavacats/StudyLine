// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerCharacterState.h"
#include "Player/PlayerTrace.h"
#include "Player/PlayerWeapon.h"
#include "Weapon/Weapon_Arrow.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class ZELDABOTW_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		APlayerCharacter* p2PlayerCharacter;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UPlayerCharacterState* p2PlayerSate;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UPlayerTrace* PlayerTrace;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		APlayerWeapon* PlayerWeapon;
	UPROPERTY(Category = Character, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		bool IsClimming;
	UPROPERTY(Category = Character, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		AWeapon_Arrow* CurArrrow;
	
private:
	bool IsJump;
	bool IsMove;
	bool IsBattle;
	bool IsShoot;
	bool CanShootArrow;
	bool IsSword;

	int32 WeaponIdleTime = 0;

	float playerSpeed = 0.0f;
	float playerCurSpeed = 0.0f;

	FTimerHandle AttackTimerHandle;
protected:
	virtual void BeginPlay() override;

public:
	APlayerCharacterController();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;
	virtual void Possess(APawn* aPawn) override;

	void KeyDownCheck();
	void PlayerJumpCheck();

	void ForwardBack(float NewAxisValue);
	void LeftRight(float NewAxisValue);

	void LookUpDown(float NewAxisValue);
	void Turn(float NewAxisValue);

	void PlayerJump();

	void PlayerRunStart();
	void PlayerRunStop();

	void PlayerCrouch();
	void PlayerUnCrouch();

	void PlayerTracePushCheck();
	void PlayerTraceClimmingCheck();

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

	void PlayerExtraState();

	void CounterAttackEnemy();

	void PlayerWeaponChangeLeft();
	void PlayerWeaponChangeRight();

	APlayerWeapon* getPlayerWeapon() { return PlayerWeapon; }
	UPlayerCharacterState* getPlayerState() { return p2PlayerSate; }
	APlayerCharacter* getPlayerCharacter() { return p2PlayerCharacter; }
	bool getIsMove() { return IsMove; }
	bool getIsClimming() { return IsClimming; }
	bool getIsBattle() { return IsBattle; }
	bool getIsShoot() { return IsShoot; }
	void setIsShoot(bool value) { IsShoot = value; }
	bool getCanShootArrow() { return CanShootArrow; }
	void setCanShootArrow(bool value) { CanShootArrow = value; }
	void setIsSword(bool value) { IsSword = value; }
	bool getIsSword() { return IsSword; }
	
};
