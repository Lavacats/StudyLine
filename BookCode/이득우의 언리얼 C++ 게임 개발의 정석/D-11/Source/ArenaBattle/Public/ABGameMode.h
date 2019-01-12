// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ArenaBattle.h"
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
	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	// �÷��̾ ���ӿ� �����ϴ� ���� �α���(Login)�̶� �Ѵ�.
	// �α��� �Ϸ� -> �÷��̾ ������ ���� ���� -> �÷��̾� ��Ʈ�ѷ��� ���� ����
	void AddScore(class AABPlayerController *Player);
	int32 GetScore() const;
	// ��Ż ���ھ� ���� ��ȯ�մϴ�.

private:
	UPROPERTY()
	class AABGameState* ABGameState;

	UPROPERTY()
	int32 ScoreToClear;
	// �¸����� ����
	
};
