// Fill out your copyright notice in the Description page of Project Settings.

#include "ABUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void AABUIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &AABUIPlayerController::OnGamePause);
	// InputComponent와 GaemPause 액션을 연결합니다 Input이 드어오면 OnGamePause함수를 실행합니다.
}

void AABUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ABCHECK(nullptr != UIWidgetClass);
	// UIwidetclass가 있는지 체크합니다

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	// UIWidgetInstanc 변수에 UIwidgetClass를 불러옵니다
	ABCHECK(nullptr != UIWidgetInstance);
	// UIWidgetInstance의 값이 제대로 불러와졌는지 체크합니다

	UIWidgetInstance->AddToViewport();
	// UIwidgetInstacne를 화면에 출력합니다

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	// 모드가 위젯에 포커스르 맞출수 있도록 캐쉬값을 받아옵니다
	SetInputMode(Mode);
	// InputMode를 세팅합니다
	bShowMouseCursor = true;
	// 마우스 커서 입력을 받을 수 있도록합니다
}

void AABUIPlayerController::OnGamePause()
{

}

