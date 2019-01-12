// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"
#include "ABHUDWidget.h"
#include "ABPlayerState.h"
#include "ABCharacter.h"
#include "ABGameplayWidget.h"
#include "ABGameplayResultWidget.h"
#include "ABGameState.h"

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
	static ConstructorHelpers::FClassFinder<UABGameplayWidget>UI_MENU_C(TEXT("/Game/Book/UI/UI_Menu.UI_Menu_C"));
	if (UI_MENU_C.Succeeded()) {
		MenuWidgetClass = UI_MENU_C.Class;
	}
	// UI_MENU 블루 프린트를 불러온는데 성공했다면 메뉴 위젯 클래스는 UI_MENU 블루브린트로 넣습니다.

	static ConstructorHelpers::FClassFinder<UABGamePlayResultWidget>UI_RESULT_C(TEXT("/Game/Book/UI/UI_Result.UI_Result_C"));
	if (UI_RESULT_C.Succeeded()) {
		ResultWidgetClass = UI_RESULT_C.Class;
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

void AABPlayerController::ChangedInputMode(bool bGameMode)
{
	if (bGameMode) {
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
		// BGameMode이면 GameInputMode를 InputMode에 넣어줍니다
		// 마우스 커서는 보이지 않게 합니다.
	}
	else {
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
		// BGameMode아니면  UIInputMode를 InputMode에 넣어줍니다
		// 마우스 커서는 보이게 합니다.
	}
}

void AABPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<UABGameplayWidget>(this, MenuWidgetClass);
	ABCHECK(nullptr != MenuWidget);
	// MenuWidget변수에 클래스 UABGameplayWidget를 불러옵니다
	MenuWidget->AddToViewport(3);
	// 메뉴 위젯 클래스를 뷰포트 깊이 3번 에 출력합니다.

	SetPause(true);
	// SetPause함수에 true값을 줍니다
	ChangedInputMode(false);
	// changeInputMode함수에 false값을 줍니다.(UIinput모드로 변경)
}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangedInputMode(true);
	// Input 모드를 변경합니다

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	// 플레이어 컨트롤러에서 게임에 입력을 전달하도록 하는 명령

	HUDWidget = CreateWidget<UABHUDWidget>(this, HDWidgetClass);
	// HUDWidgetCalss를 사용해 widget을 만들어 HUDWidget에 저장합니다
	ABCHECK(nullptr != HUDWidget);
	// HUDWidet이 있는지 확인합니다.
	HUDWidget->AddToViewport(1);
	// HUDWiget을 화면에 출력합니다 뷰포트 깊이 1

	ResultWidget = CreateWidget<UABGamePlayResultWidget>(this, ResultWidgetClass);
	ABCHECK(nullptr != ResultWidget);

	// 결가 위젯을 담을 UABGameplayResultWidget를 변수로 선언하고 검사합니다

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

void AABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &AABPlayerController::OnGamePause);
	// GamePuase버튼이 눌리면 OnGamePause 함수를 실행한다
}

void AABPlayerController::ShowResultUI()
{
	auto ABGameState = Cast<AABGameState>(UGameplayStatics::GetGameState(this));
	ABCHECK(nullptr != ABGameState);
	ResultWidget->BindGameState(ABGameState);
	// ABGamestate에 현재 게임 스테이트를 가져옵니다
	// 결과창에 ResultWidget를 연결합니다.

	ResultWidget->AddToViewport();

	ChangedInputMode(false);
	// 결과 위젯을 뷰포트에 더합니다
	// 인풋 모드를 바꿉니다
}
