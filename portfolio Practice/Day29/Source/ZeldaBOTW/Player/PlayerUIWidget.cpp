// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerUIWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"



void UPlayerUIWidget::SetPlayerAim(bool value)
{
	AimOnOff = value;
	PlayerAimImage = Cast<UImage>(GetWidgetFromName(TEXT("PlayerAim")));
	if (IsValid(PlayerAimImage)) {
		if (value)PlayerAimImage->SetVisibility(ESlateVisibility::Visible);
		else PlayerAimImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerUIWidget::SetArrowCount(int count)
{
	PlayerArrowCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ArrowCount")));
	if (IsValid(PlayerArrowCountText)) {
		PlayerArrowCountText->SetText(FText::FromString("ArrowCount : " + FString::FromInt(count)));
	}
}
