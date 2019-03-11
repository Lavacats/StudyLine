#pragma once

#include "ZeldaBOTW.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerCharacterState.h"
#include "Player/PlayerTrace.h"
#include "GameFramework/PlayerController.h"
#include "PlayerChracterMoveController.generated.h"

UCLASS()
class ZELDABOTW_API APlayerChracterMoveController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* p2PlayerCharacter;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPlayerCharacterState* p2PlayerSate;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPlayerTrace* PlayerTrace;
	UPROPERTY(Category = Character, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	bool IsClimming;
private:
	bool IsJump;
	bool IsMove;

	float playerSpeed = 0.0f;
	float playerCurSpeed = 0.0f;

public:
	APlayerChracterMoveController();
	
	virtual void Tick(float DeltaTime) override;

	void PlayerMoveSetting(APlayerCharacter* Character, UPlayerCharacterState* Sate, UPlayerTrace* Trace);

	void KeyDownCheck();
	void PlayerJumpCheck();

	void PlayerJump();

	void PlayerRunStart();
	void PlayerRunStop();

	void PlayerCrouch();
	void PlayerUnCrouch();

	void PlayerTracePushCheck();
	void PlayerTraceClimmingCheck();

	void PlayerExtraState();

	bool getIsMove() { return IsMove; }
	bool getIsClimming() { return IsClimming; }
	float getCurSpeed() { return playerCurSpeed; }

	void setIsMoveValue(bool value) { IsMove = value; }
	void setIIsClimmingValue(bool value) { IsClimming = value; }
};
