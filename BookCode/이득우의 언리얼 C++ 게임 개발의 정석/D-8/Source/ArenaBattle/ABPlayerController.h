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
	// 플레이어가 생성되는 시점
	virtual void Possess(APawn* aPawn) override;
	// 플레이어가 빙의하는 시점
	
protected:
	virtual void BeginPlay() override;


//------------------------------------------------------------------
//Pawn에서 이동값을 조정하는게 아닌, 플레이어 컨트롤러에서 입력값을 조정하는 방법
//protected:
//	virtual void SetupInputComponent() override;
//private:
//	void LeftRight(float NewAxisValue);
//-------------------------------------------------------------------

};
