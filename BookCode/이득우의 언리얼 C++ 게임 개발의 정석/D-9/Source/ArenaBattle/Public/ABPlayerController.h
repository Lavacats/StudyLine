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
	virtual void PostInitializeComponents() override;
	// �÷��̾ �����Ǵ� ����
	virtual void Possess(APawn* aPawn) override;
	// �÷��̾ �����ϴ� ����
	
protected:
	virtual void BeginPlay() override;


//------------------------------------------------------------------
//Pawn���� �̵����� �����ϴ°� �ƴ�, �÷��̾� ��Ʈ�ѷ����� �Է°��� �����ϴ� ���
//protected:
//	virtual void SetupInputComponent() override;
//private:
//	void LeftRight(float NewAxisValue);
//-------------------------------------------------------------------

};
