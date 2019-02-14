// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "PlayerCharacter.h"
#include "P2PlayerState.h"
#include "PlayerTrace.h"
#include "PlayerWeapon.h"
#include "Weapon_Arrow.h"
#include "GameFramework/PlayerController.h"
#include "P2PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE2_API AP2PlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* p2PlayerCharacter;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AP2PlayerState* p2PlayerSate;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	APlayerTrace* PlayerTrace;
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
	float playerSpeed = 0.0f;
	float playerCurSpeed = 0.0f;

protected:
	virtual void BeginPlay() override;

public:
	AP2PlayerController();

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

	void ShootArrow();


	APlayerWeapon* getPlayerWeapon() { return PlayerWeapon; }
	AP2PlayerState* getPlayerState() { return p2PlayerSate; }
	APlayerCharacter* getPlayerCharacter() {return p2PlayerCharacter;}
	bool getIsMove() { return IsMove; }
	bool getIsClimming() { return IsClimming; }
	bool getIsBattle() { return IsBattle; }
	bool getIsShoot() { return IsShoot;}
	void setIsShoot(bool value) { IsShoot = value; }
	bool getCanShootArrow() { return CanShootArrow; }
	void setCanShootArrow(bool value) { CanShootArrow = value; }
};
