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
	// ������ ��ư�� Ŭ������ �ְ� ��ư Ŭ���� ������ �Լ��� �ֽ��ϴ�.
}

void UABGameplayWidget::OnResumeClicked()
{
	auto ABPlayerController = Cast<AABPlayerController>(GetOwningPlayer());
	ABCHECK(nullptr != ABPlayerController);
	//AABPlayerController�� �ҷ����� Ȯ���մϴ�.

	RemoveFromParent();
	// UI�ý��ۿ��� ����Ʈ�� ����� �ڽ��� �����ϴ� �Լ��Դϴ�.
	ABPlayerController->ChangedInputMode(true);
	ABPlayerController->SetPause(false);
	// ABPlayerConroller�� �Է¸�带 �ٲپ��ݴϴ�.
}

void UABGameplayWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
	// Title������ �̵��մϴ�
}

void UABGameplayWidget::OnRetryGameClicked()
{
	auto ABPlayerController = Cast<AABPlayerController>(GetOwningPlayer());
	ABCHECK(nullptr != ABPlayerController);
	// ABPlayerControllerŬ������ �ҷ����� Ȯ���մϴ�.
	ABPlayerController->RestartLevel();
	//ABPlayerController�� �ִ� RestartLevel�Լ��� �����մϴ�.
}
