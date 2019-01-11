// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"
#include "ABHUDWidget.h"
#include "ABPlayerState.h"
#include "ABCharacter.h"

AABPlayerController::AABPlayerController()
{
	static ConstructorHelpers::FClassFinder<UABHUDWidget> UI_HUD_C(TEXT("/Game/Book/UI/UI_HUD.UI_HUD_C"));
	// UI_HUD 정보를 불러옵니다
	if (UI_HUD_C.Succeeded())
		// 불러오는데 성공했다면
	{
		HDWidgetClass = UI_HUD_C.Class;
		// 위젯클래스에 UI_HUD_C의 클래스를 입력합니다.
	}
}

void AABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}


void AABPlayerController::Possess(APawn * aPawn)
{
	ABLOG_S(Warning);
	Super::Possess(aPawn);
}

UABHUDWidget * AABPlayerController::GetHUDWidget() const
{
	return HUDWidget;
	// HUDWidget값을 반환합니다.
}

void AABPlayerController::NPCKill(AABCharacter * KilledNPC) const
{
	ABPlayerState->AddExp(KilledNPC->GetExp());
	// 플레이어는 죽인 NPC에서 경험치를 받는다.
}

void AABPlayerController::AddGameScore() const
{
	ABPlayerState->AddGameScore();
	// ABPlayerState의 AddGameScore함수를 실행시킵니다.
}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	// 플레이어 컨트롤러에서 게임에 입력을 전달하도록 하는 명령

	HUDWidget = CreateWidget<UABHUDWidget>(this, HDWidgetClass);
	// HUDWidgetCalss를 사용해 widget을 만들어 HUDWidget에 저장합니다
	HUDWidget->AddToViewport();
	// HUDWiget을 화면에 출력합니다 뷰포트

	//auto ABPlayerState = Cast<AABPlayerState>(PlayerState);
	ABPlayerState = Cast<AABPlayerState>(PlayerState);
	// ABPlayerState 정보를 AABPlayerState에서 가져옵니다
	ABCHECK(nullptr != ABPlayerState);
	// ABPlayerState 가 있는지 확인합니다
	HUDWidget->BindPlayerState(ABPlayerState);
	// ABPlayerSate와 HUDWidget정보를 연결합니다
	ABPlayerState->OnPlayerStateChanged.Broadcast();
	// AbPlayerState에 있는 OnPlayerStateChange 함수에 있는 딜리게이트 함수를 실행합니다
}
//
//void AABPlayerController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//	InputComponent->BindAxis(TEXT("LeftRight"), this, &AABPlayerController::LeftRight);
//}
//
//void AABPlayerController::LeftRight(float NewAxisValue)
//{
//	// 입력
//}
