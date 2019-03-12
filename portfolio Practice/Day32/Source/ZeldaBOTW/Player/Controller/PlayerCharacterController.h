#pragma once

#include "ZeldaBOTW.h"
#include "Player/PlayerCharacter.h"
#include "Player/PlayerCharacterState.h"
#include "Player/PlayerTrace.h"
#include "Player/PlayerWeapon.h"
#include "Weapon/Weapon_Arrow.h"

#include "PlayerChracterMoveController.h"
#include "PlayerCharacterBattleController.h"

#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

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
		APlayerChracterMoveController* MoveController;
	UPROPERTY(Category = Character, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		APlayerCharacterBattleController* BattleController;
	
protected:
	virtual void BeginPlay() override;

public:
	APlayerCharacterController();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;
	virtual void Possess(APawn* aPawn) override;

	void KeyDownCheck();

	void ForwardBack(float NewAxisValue);
	void LeftRight(float NewAxisValue);

	void LookUpDown(float NewAxisValue);
	void Turn(float NewAxisValue);

	APlayerWeapon* getPlayerWeapon() { return PlayerWeapon; }
	UPlayerCharacterState* getPlayerState() { return p2PlayerSate; }
	APlayerCharacter* getPlayerCharacter() { return p2PlayerCharacter; }
	APlayerChracterMoveController* getMoveController() { return MoveController; }
	APlayerCharacterBattleController* getBattleController() { return BattleController; }

	
};
