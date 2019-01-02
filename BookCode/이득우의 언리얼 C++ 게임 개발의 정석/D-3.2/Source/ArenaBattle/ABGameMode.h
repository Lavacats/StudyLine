// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "ABPawn.h"
#include "ABPlayerController.h"

#include "GameFramework/GameModeBase.h"
#include "ABGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AABGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	// 플레이어가 게임에 입장하는 것을 로그인(Login)이라 한다.
	// 로그인 완료 -> 플레이어가 조종할 폰을 생성 -> 플레이어 컨트롤러가 폰에 빙의

	
};
