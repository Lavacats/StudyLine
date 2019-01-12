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
	// UI_HUD ������ �ҷ��ɴϴ�
	if (UI_HUD_C.Succeeded())
		// �ҷ����µ� �����ߴٸ�
	{
		HDWidgetClass = UI_HUD_C.Class;
		// ����Ŭ������ UI_HUD_C�� Ŭ������ �Է��մϴ�.
	}
	static ConstructorHelpers::FClassFinder<UABGameplayWidget>UI_MENU_C(TEXT("/Game/Book/UI/UI_Menu.UI_Menu_C"));
	if (UI_MENU_C.Succeeded()) {
		MenuWidgetClass = UI_MENU_C.Class;
	}
	// UI_MENU ��� ����Ʈ�� �ҷ��´µ� �����ߴٸ� �޴� ���� Ŭ������ UI_MENU ���기Ʈ�� �ֽ��ϴ�.

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
	// HUDWidget���� ��ȯ�մϴ�.
}

void AABPlayerController::NPCKill(AABCharacter * KilledNPC) const
{
	ABPlayerState->AddExp(KilledNPC->GetExp());
	// �÷��̾�� ���� NPC���� ����ġ�� �޴´�.
}

void AABPlayerController::AddGameScore() const
{
	ABPlayerState->AddGameScore();
	// ABPlayerState�� AddGameScore�Լ��� �����ŵ�ϴ�.
}

void AABPlayerController::ChangedInputMode(bool bGameMode)
{
	if (bGameMode) {
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
		// BGameMode�̸� GameInputMode�� InputMode�� �־��ݴϴ�
		// ���콺 Ŀ���� ������ �ʰ� �մϴ�.
	}
	else {
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
		// BGameMode�ƴϸ�  UIInputMode�� InputMode�� �־��ݴϴ�
		// ���콺 Ŀ���� ���̰� �մϴ�.
	}
}

void AABPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<UABGameplayWidget>(this, MenuWidgetClass);
	ABCHECK(nullptr != MenuWidget);
	// MenuWidget������ Ŭ���� UABGameplayWidget�� �ҷ��ɴϴ�
	MenuWidget->AddToViewport(3);
	// �޴� ���� Ŭ������ ����Ʈ ���� 3�� �� ����մϴ�.

	SetPause(true);
	// SetPause�Լ��� true���� �ݴϴ�
	ChangedInputMode(false);
	// changeInputMode�Լ��� false���� �ݴϴ�.(UIinput���� ����)
}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangedInputMode(true);
	// Input ��带 �����մϴ�

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	// �÷��̾� ��Ʈ�ѷ����� ���ӿ� �Է��� �����ϵ��� �ϴ� ���

	HUDWidget = CreateWidget<UABHUDWidget>(this, HDWidgetClass);
	// HUDWidgetCalss�� ����� widget�� ����� HUDWidget�� �����մϴ�
	ABCHECK(nullptr != HUDWidget);
	// HUDWidet�� �ִ��� Ȯ���մϴ�.
	HUDWidget->AddToViewport(1);
	// HUDWiget�� ȭ�鿡 ����մϴ� ����Ʈ ���� 1

	ResultWidget = CreateWidget<UABGamePlayResultWidget>(this, ResultWidgetClass);
	ABCHECK(nullptr != ResultWidget);

	// �ᰡ ������ ���� UABGameplayResultWidget�� ������ �����ϰ� �˻��մϴ�

	//auto ABPlayerState = Cast<AABPlayerState>(PlayerState);
	ABPlayerState = Cast<AABPlayerState>(PlayerState);
	// ABPlayerState ������ AABPlayerState���� �����ɴϴ�
	ABCHECK(nullptr != ABPlayerState);
	// ABPlayerState �� �ִ��� Ȯ���մϴ�
	HUDWidget->BindPlayerState(ABPlayerState);
	// ABPlayerSate�� HUDWidget������ �����մϴ�
	ABPlayerState->OnPlayerStateChanged.Broadcast();
	// AbPlayerState�� �ִ� OnPlayerStateChange �Լ��� �ִ� ��������Ʈ �Լ��� �����մϴ�
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
//	// �Է�
//}

void AABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &AABPlayerController::OnGamePause);
	// GamePuase��ư�� ������ OnGamePause �Լ��� �����Ѵ�
}

void AABPlayerController::ShowResultUI()
{
	auto ABGameState = Cast<AABGameState>(UGameplayStatics::GetGameState(this));
	ABCHECK(nullptr != ABGameState);
	ResultWidget->BindGameState(ABGameState);
	// ABGamestate�� ���� ���� ������Ʈ�� �����ɴϴ�
	// ���â�� ResultWidget�� �����մϴ�.

	ResultWidget->AddToViewport();

	ChangedInputMode(false);
	// ��� ������ ����Ʈ�� ���մϴ�
	// ��ǲ ��带 �ٲߴϴ�
}
