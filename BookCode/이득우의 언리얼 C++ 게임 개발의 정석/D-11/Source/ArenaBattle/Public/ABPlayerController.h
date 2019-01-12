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
	// 생성자

	virtual void PostInitializeComponents() override;
	// 플레이어가 생성되는 시점
	virtual void Possess(APawn* aPawn) override;
	// 플레이어가 빙의하는 시점

	class UABHUDWidget* GetHUDWidget() const;
	//// HUDWidget 정보를 반환합니다.
	void NPCKill(class AABCharacter* KilledNPC)const;
	// NPC를 죽였다는것을 화인하는 함수
	
	void AddGameScore() const;
	// 게임 스코어를 1점 더합니다.

	void ChangedInputMode(bool bGameMode = true);
	// Input모델을 바꿉니다.

	void ShowResultUI();
	// 결과UI를 볼 함수

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UABHUDWidget> HDWidgetClass;
	// Subclassof 전달되는 UABHUDWidget을 런타임에서 확인할 수 있다

	UPROPERTY()
	class UABHUDWidget* HUDWidget;
	// 플레이어의 정보를 표시할 UI

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UABGameplayWidget>MenuWidgetClass;
	// 게임 플레이 위젯들을 관리할 menuWidgetclass 여러 UI를 관리한다.

	virtual void SetupInputComponent() override;
	// 입력 값을 설정하는 함수

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UABGamePlayResultWidget>ResultWidgetClass;
private:
	void OnGamePause();

	UPROPERTY()
	class UABGamePlayResultWidget* ResultWidget;

	UPROPERTY()
	class AABPlayerState* ABPlayerState;
	// 플레이어 스텟

	UPROPERTY()
	class UABGameplayWidget* MenuWidget;
	// 메뉴 위젯 클래스입니다.

	FInputModeGameOnly GameInputMode;
	// 게임 모드 인풋
	FInputModeUIOnly UIInputMode;
	// UI 모드 인풋

	//UPROPERTY()
	//class UABGameplayResultWidget* ResultWidget;

//------------------------------------------------------------------
//Pawn에서 이동값을 조정하는게 아닌, 플레이어 컨트롤러에서 입력값을 조정하는 방법
//protected:
//	virtual void SetupInputComponent() override;
//private:
//	void LeftRight(float NewAxisValue);
//-------------------------------------------------------------------

};
