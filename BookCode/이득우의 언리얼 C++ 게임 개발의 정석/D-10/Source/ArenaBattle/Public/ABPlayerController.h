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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UABHUDWidget> HDWidgetClass;
	// Subclassof ���޵Ǵ� UABHUDWidget�� ��Ÿ�ӿ��� Ȯ���� �� �ִ�

	UPROPERTY()
	class UABHUDWidget* HUDWidget;
	// �÷��̾��� ������ ǥ���� UI

private:
	UPROPERTY()
	class AABPlayerState* ABPlayerState;
	// �÷��̾� ����

//------------------------------------------------------------------
//Pawn���� �̵����� �����ϴ°� �ƴ�, �÷��̾� ��Ʈ�ѷ����� �Է°��� �����ϴ� ���
//protected:
//	virtual void SetupInputComponent() override;
//private:
//	void LeftRight(float NewAxisValue);
//-------------------------------------------------------------------

};
