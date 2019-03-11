// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerUIWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

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
		PlayerArrowCountText->SetText(FText::FromString("ArrowCount : " + FString::FromInt(count)));
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

	MessageBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("MessageLog")));
	for (int i = 0; i <3; i++) {
		int index = i + 1;
		UTextBlock* PlayerArrowCountText = Cast<UTextBlock>(MessageBox->GetChildAt(i));
		UTextBlock* pre_PlayerArrowCountText = Cast<UTextBlock>(MessageBox->GetChildAt(index));
		if (index==3) {
			PlayerArrowCountText->SetText(FText::FromString("Cur HP : " + FString::FromInt(curHP)));
		}
		else {
			PlayerArrowCountText->SetText(pre_PlayerArrowCountText->GetText());
		}
	}
}

void UPlayerUIWidget::SetPontAlpha(int index)
{
	switch (index) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	}
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &APlayerCharacterBattleController::WeaponToIdleTimer, 5.0f, true, 0.0f);

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
