// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/PlayerController.h"
#include "ABPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AABPlayerController();
	// ������

	virtual void PostInitializeComponents() override;
	// �÷��̾ �����Ǵ� ����
	virtual void Possess(APawn* aPawn) override;
	// �÷��̾ �����ϴ� ����

	class UABHUDWidget* GetHUDWidget() const;
	//// HUDWidget ������ ��ȯ�մϴ�.
	void NPCKill(class AABCharacter* KilledNPC)const;
	// NPC�� �׿��ٴ°��� ȭ���ϴ� �Լ�
	
	void AddGameScore() const;
	// ���� ���ھ 1�� ���մϴ�.

	void ChangedInputMode(bool bGameMode = true);
	// Input���� �ٲߴϴ�.

	void ShowResultUI();
	// ���UI�� �� �Լ�

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UABHUDWidget> HDWidgetClass;
	// Subclassof ���޵Ǵ� UABHUDWidget�� ��Ÿ�ӿ��� Ȯ���� �� �ִ�

	UPROPERTY()
	class UABHUDWidget* HUDWidget;
	// �÷��̾��� ������ ǥ���� UI

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UABGameplayWidget>MenuWidgetClass;
	// ���� �÷��� �������� ������ menuWidgetclass ���� UI�� �����Ѵ�.

	virtual void SetupInputComponent() override;
	// �Է� ���� �����ϴ� �Լ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UABGamePlayResultWidget>ResultWidgetClass;
private:
	void OnGamePause();

	UPROPERTY()
	class UABGamePlayResultWidget* ResultWidget;

	UPROPERTY()
	class AABPlayerState* ABPlayerState;
	// �÷��̾� ����

	UPROPERTY()
	class UABGameplayWidget* MenuWidget;
	// �޴� ���� Ŭ�����Դϴ�.

	FInputModeGameOnly GameInputMode;
	// ���� ��� ��ǲ
	FInputModeUIOnly UIInputMode;
	// UI ��� ��ǲ

	//UPROPERTY()
	//class UABGameplayResultWidget* ResultWidget;

//------------------------------------------------------------------
//Pawn���� �̵����� �����ϴ°� �ƴ�, �÷��̾� ��Ʈ�ѷ����� �Է°��� �����ϴ� ���
//protected:
//	virtual void SetupInputComponent() override;
//private:
//	void LeftRight(float NewAxisValue);
//-------------------------------------------------------------------

};
