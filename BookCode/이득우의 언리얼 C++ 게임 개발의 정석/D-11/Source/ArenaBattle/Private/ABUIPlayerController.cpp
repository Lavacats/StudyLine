// Fill out your copyright notice in the Description page of Project Settings.

#include "ABUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void AABUIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &AABUIPlayerController::OnGamePause);
	// InputComponent�� GaemPause �׼��� �����մϴ� Input�� ������ OnGamePause�Լ��� �����մϴ�.
}

void AABUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ABCHECK(nullptr != UIWidgetClass);
	// UIwidetclass�� �ִ��� üũ�մϴ�

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	// UIWidgetInstanc ������ UIwidgetClass�� �ҷ��ɴϴ�
	ABCHECK(nullptr != UIWidgetInstance);
	// UIWidgetInstance�� ���� ����� �ҷ��������� üũ�մϴ�

	UIWidgetInstance->AddToViewport();
	// UIwidgetInstacne�� ȭ�鿡 ����մϴ�

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	// ��尡 ������ ��Ŀ���� ����� �ֵ��� ĳ������ �޾ƿɴϴ�
	SetInputMode(Mode);
	// InputMode�� �����մϴ�
	bShowMouseCursor = true;
	// ���콺 Ŀ�� �Է��� ���� �� �ֵ����մϴ�
}

void AABUIPlayerController::OnGamePause()
{

}

