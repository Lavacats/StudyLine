#pragma once

#include "ZeldaBOTW.h"
#include "PlayerChracterMoveController.h"
#include "PlayerCharacterBattleController.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

UCLASS()
class ZELDABOTW_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

private:
	bool showInventoryUI;

private:
	class APlayerCharacter* PlayerCharacter;
	class UPlayerCharacterState* PlayerCharacterState;
	class UPlayerTrace* PlayerTrace;
	class APlayerWeapon* PlayerWeapon;
	APlayerChracterMoveController* MoveController;
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

	void ShowInventoryUI();

	bool getShowInventoryUIValue() { return showInventoryUI; }
	class APlayerWeapon* getPlayerWeapon() { return PlayerWeapon; }
	class UPlayerCharacterState* getPlayerState() { return PlayerCharacterState; }
	class APlayerCharacter* getPlayerCharacter() { return PlayerCharacter; }
	APlayerChracterMoveController* getMoveController() { return MoveController; }
	APlayerCharacterBattleController* getBattleController() { return BattleController; }

	
};
