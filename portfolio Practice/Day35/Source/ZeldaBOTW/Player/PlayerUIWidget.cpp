// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerUIWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/CanvasPanel.h"


UPlayerUIWidget::UPlayerUIWidget(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

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
		if (PlayerAimImage->Visibility == ESlateVisibility::Visible) {
			PlayerArrowCountText->SetText(FText::FromString("ArrowCount : " + FString::FromInt(count)));
			PlayerArrowCountText->SetVisibility(ESlateVisibility::Visible);

		}
		else {
			PlayerArrowCountText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UPlayerUIWidget::SetHP(int maxHP, int curHP)
{
	if (curHP > maxHP)curHP = maxHP;
	HeartBox = Cast<UWrapBox>(GetWidgetFromName(TEXT("HP_BOX")));
	int heartCount = maxHP / 4;
	if (heartCount > HeartBox->GetChildrenCount()) {
		int value = heartCount - HeartBox->GetChildrenCount();
		for (int i = 0; i < value; i++) {
			UImage* hearImage2 = NewObject<UImage>();
			UTexture2D* Texture = getTexture(4);
			hearImage2->SetBrushFromTexture(Texture);
			HeartBox->AddChild(hearImage2);
			hearImage2->Brush.ImageSize = FVector2D(70.0f, 70.0f);
		}
	}

	for (int i = heartCount-1; i >= 0; i--) {
		int curHearImage = curHP - 4 * i;
		UTexture2D* Texture = getTexture(curHearImage);
		UImage* changeImage = Cast<UImage>(HeartBox->GetChildAt(i));
		if (IsValid(changeImage)) {
			changeImage->SetBrushFromTexture(Texture);
		}
	}
}

void UPlayerUIWidget::SetPontAlpha(UVerticalBox* MessageBox)
{
	MessageBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("MessageLog")));
	UTextBlock* Box_0 = Cast<UTextBlock>(MessageBox->GetChildAt(0));
	UTextBlock* Box_1 = Cast<UTextBlock>(MessageBox->GetChildAt(1));
	UTextBlock* Box_2 = Cast<UTextBlock>(MessageBox->GetChildAt(2));

	Box_0->SetColorAndOpacity(Box_1->ColorAndOpacity);
	Box_1->SetColorAndOpacity(Box_2->ColorAndOpacity);
	Box_2->SetColorAndOpacity(FSlateColor(FLinearColor(Box_2->ColorAndOpacity.GetSpecifiedColor().R, Box_2->ColorAndOpacity.GetSpecifiedColor().G, Box_2->ColorAndOpacity.GetSpecifiedColor().B, 1.0f)));
	

	GetWorld()->GetTimerManager().ClearTimer(Font1_TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(Font1_TimerHandle, this, &UPlayerUIWidget::FontHide, 0.1f, true, 1.0f);
}

void UPlayerUIWidget::FontHide()
{
	MessageBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("MessageLog")));
	UTextBlock* Box_0 = Cast<UTextBlock>(MessageBox->GetChildAt(0));
	UTextBlock* Box_1 = Cast<UTextBlock>(MessageBox->GetChildAt(1));
	UTextBlock* Box_2 = Cast<UTextBlock>(MessageBox->GetChildAt(2));
	Box_0->SetColorAndOpacity(FSlateColor(FLinearColor(Box_0->ColorAndOpacity.GetSpecifiedColor().R, Box_0->ColorAndOpacity.GetSpecifiedColor().G, Box_0->ColorAndOpacity.GetSpecifiedColor().B, Box_0->ColorAndOpacity.GetSpecifiedColor().A - 0.025f)));
	Box_1->SetColorAndOpacity(FSlateColor(FLinearColor(Box_1->ColorAndOpacity.GetSpecifiedColor().R, Box_1->ColorAndOpacity.GetSpecifiedColor().G, Box_1->ColorAndOpacity.GetSpecifiedColor().B, Box_1->ColorAndOpacity.GetSpecifiedColor().A - 0.025f)));
	Box_2->SetColorAndOpacity(FSlateColor(FLinearColor(Box_2->ColorAndOpacity.GetSpecifiedColor().R, Box_2->ColorAndOpacity.GetSpecifiedColor().G, Box_2->ColorAndOpacity.GetSpecifiedColor().B, Box_2->ColorAndOpacity.GetSpecifiedColor().A - 0.025f)));
	
}

void UPlayerUIWidget::ShowInventory()
{
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	auto InventoryUI = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("InventoryUI")));
	auto IdleUI = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("IdleUI")));
	if (IsValid(InventoryUI) && IsValid(IdleUI)) {
		if (InventoryUI->Visibility == ESlateVisibility::Visible) {
			InventoryUI->SetVisibility(ESlateVisibility::Hidden);
			IdleUI->SetVisibility(ESlateVisibility::Visible);
			InventoryActive = false;
			MyController->bShowMouseCursor = false;
			MyController->bEnableClickEvents = false;
			MyController->bEnableMouseOverEvents = false;

		}
		else {
			InventoryUI->SetVisibility(ESlateVisibility::Visible);
			IdleUI->SetVisibility(ESlateVisibility::Hidden);
			InventoryActive = true;
			MyController->bShowMouseCursor = true;
			MyController->bEnableClickEvents = true;
			MyController->bEnableMouseOverEvents = true;
		}
	}
}

void UPlayerUIWidget::PrintMessageBox(FString Message)
{
	MessageBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("MessageLog")));
	for (int i = 0; i < 3; i++) {
		int index = i + 1;
		UTextBlock* PlayerArrowCountText = Cast<UTextBlock>(MessageBox->GetChildAt(i));
		UTextBlock* pre_PlayerArrowCountText = Cast<UTextBlock>(MessageBox->GetChildAt(index));
		if (index == 3) {
			PlayerArrowCountText->SetText(FText::FromString(Message));
		}
		else {
			PlayerArrowCountText->SetText(pre_PlayerArrowCountText->GetText());
		}
	}
	SetPontAlpha(MessageBox);
}

UTexture2D * UPlayerUIWidget::getTexture(int num)
{
	FString Path;
	if (num < 0)num = 0;
	else if (num > 4)num = 4;
	switch (num) {
		case 0:
			 Path = FString("/Game/UI/UI_IMAGE/Heart/Heart0.Heart0");
			break;
		case 1:
			 Path = FString("/Game/UI/UI_IMAGE/Heart/Heart1.Heart1");
			break;
		case 2:
			 Path = FString("/Game/UI/UI_IMAGE/Heart/Heart2.Heart2");
			break;
		case 3:
			 Path = FString("/Game/UI/UI_IMAGE/Heart/Heart3.Heart3");
			break;
		case 4:
			 Path = FString("/Game/UI/UI_IMAGE/Heart/Heart4.Heart4");
			break;
	}
	UTexture2D* returnTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *Path));

	return returnTexture;
}
