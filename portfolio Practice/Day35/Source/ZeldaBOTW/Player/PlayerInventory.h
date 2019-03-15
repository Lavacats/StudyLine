// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "Weapon/Weapon_Arrow.h"
#include "Weapon/Weapon_Equip.h"
#include "Object/ItemClassFood.h"
#include "Object/ItemClassMaterial.h"
#include "Components/ActorComponent.h"
#include "PlayerInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZELDABOTW_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TArray<AWeapon_Equip*> Weapon_BowList;
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TArray<AWeapon_Equip*> Weapon_ShieldList;
	UPROPERTY(EditAnywhere, Category = Weapon)
	TArray<AWeapon_Equip*> Weapon_SwordList;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TArray<AItemClassFood*> Item_FoodList;
	UPROPERTY(EditAnywhere, Category = Weapon)
	TArray<AItemClassMaterial*> Item_MaterialList;
public:	
	UPlayerInventory();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddSwordInventory(AWeapon_Equip* sword);
	void AddBowdInventory(AWeapon_Equip* Bow);
	void AddShieldInventory(AWeapon_Equip* Shield);
	void AddFoodInventory(AItemClassFood* Food);
	void AddMaterialInventory(AItemClassMaterial* Material);

	TArray<AWeapon_Equip*> getWeapon_BowList() { return Weapon_BowList; }
	TArray<AWeapon_Equip*> getWeapon_SwordList() { return Weapon_SwordList; }
	TArray<AWeapon_Equip*> getWeapon_ShieldList() { return Weapon_ShieldList; }
	TArray<AItemClassFood*> getItem_FoodList() { return Item_FoodList; }
	TArray<AItemClassMaterial*> getItem_MaterialList() { return Item_MaterialList; }
};
