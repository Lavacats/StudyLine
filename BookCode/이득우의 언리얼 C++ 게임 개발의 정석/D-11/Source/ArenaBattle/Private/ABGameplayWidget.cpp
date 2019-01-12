// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameplayWidget.h"
#include "Components/Button.h"
#include "ABPlayerController.h"

void UABGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (nullptr != ResumeButton) {
		ResumeButton->OnClicked.AddDynamic(this, &UABGameplayWidget::OnResumeClicked);
	}

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (nullptr != ReturnToTitleButton) {
		ReturnToTitleButton->OnClicked.AddDynamic(this, &UABGameplayWidget::OnReturnToTitleClicked);
	}

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
	if (nullptr != RetryGameButton) {
		RetryGameButton->OnClicked.AddDynamic(this, &UABGameplayWidget::OnRetryGameClicked);
	}
	// 각각의 버튼에 클래스를 넣고 버튼 클릭시 실행할 함수를 넣습니다.
}

void UABGameplayWidget::OnResumeClicked()
{
	auto ABPlayerController = Cast<AABPlayerController>(GetOwningPlayer());
	ABCHECK(nullptr != ABPlayerController);
	//AABPlayerController를 불러오고 확입합니다.

	RemoveFromParent();
	// UI시스템에서 뷰포트에 띄워진 자신을 제거하는 함수입니다.
	ABPlayerController->ChangedInputMode(true);
	ABPlayerController->SetPause(false);
	// ABPlayerConroller의 입력모드를 바꾸어줍니다.
}

void UABGameplayWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
	// Title레벨로 이동합니다
}

void UABGameplayWidget::OnRetryGameClicked()
{
	auto ABPlayerController = Cast<AABPlayerController>(GetOwningPlayer());
	ABCHECK(nullptr != ABPlayerController);
	// ABPlayerController클래스를 불러오고 확인합니다.
	ABPlayerController->RestartLevel();
	//ABPlayerController에 있는 RestartLevel함수를 실행합니다.
}
