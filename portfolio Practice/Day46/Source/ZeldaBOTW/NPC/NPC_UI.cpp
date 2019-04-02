// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC_UI.h"
#include "NPC/NPC_Shop.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Player/Controller/PlayerCharacterController.h"
#include "Player/Controller/PlayerChracterMoveController.h"
#include "Player/PlayerInventory.h"
#include "Player/PlayerCharacter.h"
#include "Weapon/Weapon_Equip.h"

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
			
			curItem.ItemName = totalitemClass->getStructItem()[i].ItemName;
			curItem.ItemImage = totalitemClass->getStructItem()[i].ItemImage;
			curItem.ItemInformation = totalitemClass->getStructItem()[i].ItemInformation;
			curItem.ItemPrice = totalitemClass->getStructItem()[i].ItemPrice;
			curItem.ItemType = totalitemClass->getStructItem()[i].ItemType;
			curItem.ItemMesh = totalitemClass->getStructItem()[i].ItemMesh;
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

void UNPC_UI::OnOffShopUI()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PController = Cast< APlayerCharacterController>(PlayerController);
	auto PCMoveController = PController->getMoveController();
	if (IsValid(PController)) {
		PCMoveController->PlayerExtraState();
	}
}

void UNPC_UI::BuyItemShop()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PController = Cast< APlayerCharacterController>(PlayerController);
	auto PlayerInventory = PController->getPlayerCharacter()->getPlayerInvenroty();
	if (curItem.ItemPrice <= PlayerInventory->getPlayerMoneyCount()) {
		int value = PlayerInventory->getPlayerMoneyCount() - curItem.ItemPrice;
		PlayerInventory->setPlayerMoneyCount(value);

		if (curItem.ItemType == ItemTypeValue::ItemType_Weapon || curItem.ItemType == ItemTypeValue::ItemType_Bow || curItem.ItemType == ItemTypeValue::ItemType_Shield)
		{
			WeaponClass = AWeapon_Equip::StaticClass();
			auto weapon = GetWorld()->SpawnActor<AWeapon_Equip>(WeaponClass, PController->getPlayerCharacter()->GetActorLocation(), FRotator::ZeroRotator);
			switch (curItem.ItemType) {
			case ItemTypeValue::ItemType_Weapon:
				weapon->setItemName(curItem.ItemName);
				weapon->setItemInformation(curItem.ItemInformation);
				weapon->setItemImage(curItem.ItemImage);
				weapon->setItemPrice(curItem.ItemPrice);
				weapon->setItemTypeValue(curItem.ItemType);
				weapon->getWeaponMesh()->SetStaticMesh(curItem.ItemMesh);
				PlayerInventory->AddSwordInventory(weapon);
				break;
			case ItemTypeValue::ItemType_Bow:
				break;
			case ItemTypeValue::ItemType_Shield:
				break;
			}
		}

	}
}

void UNPC_UI::SellPlayerInventory()
{
	auto MenuUI = Cast<UCanvasPanel>(GetWidgetFromName("BUY_UI"));
	MenuUI->SetVisibility(ESlateVisibility::Hidden);

	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto PController = Cast< APlayerCharacterController>(PlayerController);
	PController->getPlayerCharacter()->getPlayerUI()->ShowInventory();
	PController->getPlayerCharacter()->getPlayerUI()->ShowShopButton();
}