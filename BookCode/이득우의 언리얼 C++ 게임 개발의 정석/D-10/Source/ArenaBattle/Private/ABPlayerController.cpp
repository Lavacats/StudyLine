// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPlayerController.h"
#include "ABHUDWidget.h"
#include "ABPlayerState.h"
#include "ABCharacter.h"

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

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	// �÷��̾� ��Ʈ�ѷ����� ���ӿ� �Է��� �����ϵ��� �ϴ� ���

	HUDWidget = CreateWidget<UABHUDWidget>(this, HDWidgetClass);
	// HUDWidgetCalss�� ����� widget�� ����� HUDWidget�� �����մϴ�
	HUDWidget->AddToViewport();
	// HUDWiget�� ȭ�鿡 ����մϴ� ����Ʈ

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
