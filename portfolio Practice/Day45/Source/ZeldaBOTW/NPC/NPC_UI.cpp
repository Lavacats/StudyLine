// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_UI.h"
#include "NPC/NPC_Shop.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UNPC_UI::ItemImageChange(UImage * image)
{
	UTexture2D* tex2 = Cast<UTexture2D>(image->Brush.GetResourceObject());
	auto MenuUI = Cast<UImage>(GetWidgetFromName("ItemImageUI"));
	if (IsValid(MenuUI)) {
		MenuUI->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
		MenuUI->SetBrushFromTexture(tex2);
	}

	auto ItemName = Cast<UTextBlock>(GetWidgetFromName("ItemName"));
	auto ItemInformation = Cast<UTextBlock>(GetWidgetFromName("ItemInformation"));
	for (int i = 0; i < totalitemClass->getStructItem().Num(); i++) {
		if (totalitemClass->getStructItem()[i].ItemImage == tex2) {
			ItemName->SetText(FText::FromName(totalitemClass->getStructItem()[i].ItemName));
			ItemInformation->SetText(FText::FromName(FName(*totalitemClass->getStructItem()[i].ItemInformation)));
			break;
		}
	}

}

void UNPC_UI::setNpcShop(ANPC_Shop * shop)
{  
	if (IsValid(shop)) {
		totalitemClass = shop->getTotalItemClass();
		count = 1;
	}
}

