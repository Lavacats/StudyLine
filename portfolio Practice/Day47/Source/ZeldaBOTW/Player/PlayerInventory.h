// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "Object/TotalItemClass.h"
#include "Weapon/Weapon_Arrow.h"
#include "Weapon/Weapon_Equip.h"
#include "Object/ItemClass.h"
#include "Object/ItemClassFood.h"
#include "Object/ItemClassMaterial.h"

#include "Components/ActorComponent.h"
#include "PlayerInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZELDABOTW_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()
private:
	TArray<AWeapon_Equip*> Weapon_BowList;
	TArray<AWeapon_Equip*> Weapon_ShieldList;
	TArray<AWeapon_Equip*> Weapon_SwordList;
	TArray<AItemClassFood*> Item_FoodList;
	TArray<AItemClassMaterial*> Item_MaterialList;
	UPROPERTY(Category = Inventory, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 PlayerMoney;

	UPROPERTY(Category = Inventory, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FName			curItemName;
	UPROPERTY(Category = Inventory, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTexture2D*		curItemImage;
	UPROPERTY(Category = Inventory, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString			curItemInformation;
	UPROPERTY(Category = Inventory, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ItemTypeValue	curItemType;
	UPROPERTY(Category = Inventory, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float			curItemPrice;

public:	
	UPlayerInventory();

public:	
	FName getCurItemName() { return curItemName; }
	UTexture2D* getCurItemImage() { return curItemImage; }
	FString getCurItemInformation() { return curItemInformation; }
	ItemTypeValue getCurItemType() { return curItemType; }
	float getCurItemPrice() { return curItemPrice; }

	void AddSwordInventory(AWeapon_Equip* sword);
	void AddBowdInventory(AWeapon_Equip* Bow);
	void AddShieldInventory(AWeapon_Equip* Shield);
	void AddFoodInventory(AItemClassFood* Food);
	void AddMaterialInventory(AItemClassMaterial* Material);

	void DeleteWaepon_SwordList(AWeapon_Equip* weapon);

	void setPlayerMoneyCount(int value) { PlayerMoney = value; }

	void setCurItemName(FName itemName) { curItemName = itemName; }
	void setCurItemImage(UTexture2D* ItemTexture) { curItemImage = ItemTexture; }
	void setCurItemInformation(FString ItemInformation) { curItemInformation = ItemInformation; }
	void setCurItemType(ItemTypeValue itemType) {itemType = curItemType;}
	void setCurItemPrice(float itemPrice) { curItemPrice = itemPrice; }

	TArray<AWeapon_Equip*> getWeapon_BowList() { return Weapon_BowList; }
	TArray<AWeapon_Equip*> getWeapon_SwordList() { return Weapon_SwordList; }
	TArray<AWeapon_Equip*> getWeapon_ShieldList() { return Weapon_ShieldList; }
	TArray<AItemClassFood*> getItem_FoodList() { return Item_FoodList; }
	TArray<AItemClassMaterial*> getItem_MaterialList() { return Item_MaterialList; }

	int32 getPlayerMoneyCount() { return PlayerMoney; }
};
